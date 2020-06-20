#include "room.h"

using namespace		game;

void				room::link_obstacle_to_row(const obstacle::obstacle::ptr &obstacle, int row_index)
{
	obstacle_links.push_back(engine::scene::scene::game_object<obstacle_link>(obstacle, row_index));
}