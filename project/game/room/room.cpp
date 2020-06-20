#include "room.h"

using namespace					game;

								room::room()
{
	build_models();
	build_main_instances();
	build_unique_groups();
	offset_groups();

	for (const auto &group : groups)
		game_object::render_target(group);

	obstacles.chair = engine::scene::scene::game_object<game::obstacle::chair>(line::middle);

	link_obstacle_to_row(obstacles.chair, number_of_rows - 1);
}