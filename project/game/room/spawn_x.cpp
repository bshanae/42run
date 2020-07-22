#include "room.h"

#include "game/obstacle/chair.h"
#include "game/bonus/coin.h"
#include "game/bonus/heal.h"
#include "game/bonus/protection.h"

using namespace		game;

static line			random_line()
{
	auto			random_int = random(int_range(0, 2));

	switch (random_int)
	{
		case 0 :
			return (line::left);

		case 1 :
			return (line::middle);

		default :
			return (line::right);
	}
}

void				room::spawn_chair()
{
	auto			chair = make_shared<obstacle::chair>(random_line());
	auto			chair_as_object = static_pointer_cast<game_object>(chair);
	auto			chair_as_obstacle = static_pointer_cast<obstacle::obstacle>(chair);

	global_scene->include(chair_as_object);
	rows.back()->link_obstacle(chair_as_obstacle);
}

void				room::spawn_hollow_row()
{
	rows.back()->make_hollow(true);
}

void				room::spawn_coin()
{
	shared<row>		row = rows.back();
	auto			line = random_line();

	if (not row->is_line_free(line))
	{
		for (int i = 0; i < 5; i++)
			if (line = random_line(); row->is_line_free(line))
				break ;
		if (not row->is_line_free(line))
			return ;
	}

	auto			coin = make_shared<bonus::coin>(line);
	auto			coin_as_object = static_pointer_cast<game_object>(coin);
	auto			coin_as_bonus = static_pointer_cast<bonus::bonus>(coin);

	global_scene->include(coin_as_object);
	rows.back()->link_bonus(coin_as_bonus);
}

void				room::spawn_heal()
{
	shared<row>		row = rows.back();
	auto			line = random_line();

	if (not row->is_line_free(line))
	{
		for (int i = 0; i < 5; i++)
			if (line = random_line(); row->is_line_free(line))
				break ;
		if (not row->is_line_free(line))
			return ;
	}

	auto			heal = make_shared<bonus::heal>(line);
	auto			heal_as_object = static_pointer_cast<game_object>(heal);
	auto			heal_as_bonus = static_pointer_cast<bonus::bonus>(heal);

	global_scene->include(heal_as_object);
	rows.back()->link_bonus(heal_as_bonus);
}


void				room::spawn_protection()
{
	shared<row>		row = rows.back();
	auto			line = random_line();

	if (not row->is_line_free(line))
	{
		for (int i = 0; i < 5; i++)
			if (line = random_line(); row->is_line_free(line))
				break ;
		if (not row->is_line_free(line))
			return ;
	}

	auto			protection = make_shared<bonus::protection>(line);
	auto			protection_as_object = static_pointer_cast<game_object>(protection);
	auto			protection_as_bonus = static_pointer_cast<bonus::bonus>(protection);

	global_scene->include(protection_as_object);
	rows.back()->link_bonus(protection_as_bonus);
}