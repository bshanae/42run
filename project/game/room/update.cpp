#include "room.h"

using namespace							game;

#define INCREMENT_TILL(value, limit)	(value + 1) >= limit ? 0 : (value + 1)

void									room::update()
{
	static const vec3					size = models.room->size();

	bool								rows_was_swapped = false;

	auto								movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto								nearest_ptr = groups[nearest_index];
	auto								furthest_ptr = groups[furthest_index];

//										Rows movement
	for (auto &group : groups)
		group->translate(movement);

//										Obstacles movement
	for (auto &obstacle_link : obstacle_links)
		obstacle_link.move_to(groups[obstacle_link.read_row_index()]->translation());

//										Replacing first row with last
	if (nearest_ptr->translation().z > size.z)
	{
		rows_was_swapped = true;

		delete_obstacle(nearest_index);

		nearest_ptr->reset_translation();
		nearest_ptr->translate(furthest_ptr->translation());
		nearest_ptr->translate(row_offset);

		furthest_index = nearest_index;
		nearest_index = INCREMENT_TILL(nearest_index, number_of_rows);
	}

//										Obstacles spawning
	static int							chair_spawn_countdown = settings().chair_spawning_wait;

	if (not rows_was_swapped)
		return ;

	if (chair_spawn_countdown == 0)
	{
		spawn_chair();
		chair_spawn_countdown = random(settings().chair_spawning_frequency);
	}
	else
		chair_spawn_countdown--;
}