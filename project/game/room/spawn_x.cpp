#include "room.h"

using namespace		game;

void				room::spawn_chair()
{
	auto			random_int = random(int_range(0, 2));
	enum line		random_line;

	switch (random_int)
	{
		case 0 :
			random_line = line::left;
			break ;

		case 1 :
			random_line = line::middle;
			break ;

		default :
			random_line = line::right;
			break ;
	}

	auto			chair = make_shared<obstacle::chair>(random_line);
	auto			chair_as_object = static_pointer_cast<game_object>(chair);
	auto			chair_as_obstacle = static_pointer_cast<obstacle::obstacle>(chair);

	global().scene->include(chair_as_object);
	rows.back().link_obstacle(chair_as_obstacle);
}

void				room::spawn_hollow_row()
{
	rows.back().make_hollow(true);
}