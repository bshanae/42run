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

	rows.back().link_obstacle
	(
		static_pointer_cast<obstacle::obstacle>
		(
			scene::scene::game_object<obstacle::chair>(random_line)
		)
	);
}