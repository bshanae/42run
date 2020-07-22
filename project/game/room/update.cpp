#include "room.h"

#include "game/model_with_mods/instance.h"
#include "game/model_with_mods/group.h"

using namespace			game;

void					room::update()
{
	static const vec3	size = models.room->size();

	bool				rows_was_swapped = false;
	auto				movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto				nearest_row = rows.front();
	auto				furthest_row = rows.back();
	auto				nearest_group = nearest_row->read_group();
	auto				furthest_group = furthest_row->read_group();

//						Rows and obstacles movement
	for (auto &row : rows)
		row->move(movement);

//						Replacing first row with last
	if (nearest_group->translation().z > size.z)
	{
		rows_was_swapped = true;
		rows_swap_counter++;

		nearest_group->reset_translation();
		nearest_group->translate(furthest_group->translation());
		nearest_group->translate(row_offset);

		nearest_row->make_hollow(false);
		nearest_row->link_obstacle(nullptr);

		rows.push_back(nearest_row);
		rows.pop_front();

//						Resets hollow shading
		int				count = settings().number_of_faded_rows;

		for (auto iterator = rows.rbegin(); iterator != rows.rend(); iterator++)
			(*iterator)->make_hollow_temporarily(count-- > 0);
	}

//						Obstacles spawning
	auto				should_spawn = [](int &counter, const int_range &range_for_generation)
	{
		bool			result = false;

		if (counter == 0)
		{
			result = true;
			counter = random(range_for_generation);
		}
		else
			counter--;

		return (result);
	};

	static int			hollow_row_spawn_countdown = settings().obstacle_generation_wait;
	static int			chair_spawn_countdown = settings().obstacle_generation_wait;
	static int			coin_spawn_countdown = settings().bonus_generation_wait;
	static int			heal_spawn_countdown = settings().bonus_generation_wait;
	static int			protection_spawn_countdown = settings().bonus_generation_wait;

	if (not rows_was_swapped)
		return ;

	bool				should_spawn_hollow_row;
	bool				should_spawn_chair;
	bool				should_spawn_coin;
	bool				should_spawn_heal;
	bool				should_spawn_protection;

	should_spawn_hollow_row = should_spawn(hollow_row_spawn_countdown, settings().hollow_row_spawning_frequency);
	should_spawn_chair = should_spawn(chair_spawn_countdown, settings().chair_spawning_frequency);
	should_spawn_coin =  should_spawn(coin_spawn_countdown, settings().coin_spawning_frequency);
	should_spawn_heal =  should_spawn(heal_spawn_countdown, settings().heal_spawning_frequency);
	should_spawn_protection =  should_spawn(protection_spawn_countdown, settings().protection_spawning_frequency);

	if (should_spawn_hollow_row)
		spawn_hollow_row();
	else if (should_spawn_chair)
		spawn_chair();

	if (should_spawn_coin)
		spawn_coin();
	else if (should_spawn_heal)
		spawn_heal();
	else if (should_spawn_protection)
		spawn_protection();

//						Update values
	if (speed_factor < settings().maximum_room_speed_factor)
		speed_factor *= (1.f + settings().increase_of_room_speed);
}