#include "room.h"

using namespace							game;

void									room::update()
{
	static const vec3					size = models.room->size();

	bool								rows_was_swapped = false;

	auto								movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto								nearest_group = groups_in_order.front();
	auto								furthest_group = groups_in_order.back();

//										Rows movement
	for (auto &group : groups)
		group->translate(movement);

//										Obstacles movement
	for (auto &obstacle_link : obstacle_links)
		obstacle_link.move_to(obstacle_link.row->translation());

//										Replacing first row with last
	if (nearest_group->translation().z > size.z)
	{
		rows_was_swapped = true;

		nearest_group->reset_translation();
		nearest_group->translate(furthest_group->translation());
		nearest_group->translate(row_offset);

		pop_obstacle(nearest_group);

		groups_in_order.push_back(nearest_group);
		groups_in_order.pop_front();

//										Resets special shading
		int								count = settings().number_of_faded_rows;

		for (auto iterator = groups_in_order.rbegin(); iterator != groups_in_order.rend(); iterator++)
			(*iterator)->use_fading(count-- > 0);
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