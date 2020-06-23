#include "room.h"

using namespace			game;

void					room::update()
{
	static const vec3	size = models.room->size();

	bool				rows_was_swapped = false;

	auto				movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto				nearest_row = rows.front();
	auto				furthest_row = rows.back();

	auto				nearest_group = nearest_row.read_group();
	auto				furthest_group = furthest_row.read_group();

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

		nearest_row.make_hollow(false);
		nearest_row.unlink_obstacle();

		rows.push_back(nearest_row);
		rows.pop_front();

//						Resets hollow shading
		int				count = settings().number_of_faded_rows;

		for (auto iterator = rows.rbegin(); iterator != rows.rend(); iterator++)
			(*iterator).make_hollow_temporarily(count-- > 0);
	}

//						Obstacles spawning
	static int			chair_spawn_countdown = settings().obstacle_generation_wait;
	static int			hollow_row_spawn_countdown = settings().obstacle_generation_wait;

	if (not rows_was_swapped)
		return ;

#define PROCESS_OBSTACLE(counter, spawner, value_generator)						\
	if (counter == 0)															\
	{																			\
		spawner();																\
		counter = value_generator;												\
	}																			\
	else																		\
		counter--;

PROCESS_OBSTACLE(chair_spawn_countdown, spawn_chair, random(settings().chair_spawning_frequency));
PROCESS_OBSTACLE(hollow_row_spawn_countdown, spawn_hollow_row, random(settings().hollow_row_spawning_frequency));
}