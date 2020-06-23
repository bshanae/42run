#include "room.h"

using namespace							game;

void									room::update()
{
	static const vec3					size = models.room->size();

	bool								rows_was_swapped = false;

	auto								movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto								nearest_row = rows.front();
	auto								furthest_row = rows.back();

	auto								nearest_group = nearest_row.read_group();
	auto								furthest_group = furthest_row.read_group();

//										Rows and obstacles movement
	for (auto &row : rows)
		row.move(movement);

//										Replacing first row with last
	if (nearest_group->translation().z > size.z)
	{
		rows_was_swapped = true;

		nearest_group->reset_translation();
		nearest_group->translate(furthest_group->translation());
		nearest_group->translate(row_offset);

		nearest_row.unlink_obstacle();

		rows.push_back(nearest_row);
		rows.pop_front();

//										Resets special shading
		int								count = settings().number_of_faded_rows;

		for (auto iterator = rows.rbegin(); iterator != rows.rend(); iterator++)
			(*iterator).read_group()->hollow(count-- > 0);
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