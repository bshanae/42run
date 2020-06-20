#include "room.h"

using namespace		game;

void				room::link_obstacle_to_row(const obstacle::obstacle::ptr &obstacle, int row_index)
{
	obstacle_links.emplace_back(obstacle, row_index);
}

void 				room::delete_link(int row_index)
{

}