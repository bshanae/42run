#include "room.h"

using namespace		game;

void				room::push_obstacle(const obstacle::obstacle::ptr &obstacle)
{
	obstacle_links.emplace_back(obstacle, groups_in_order.back());
}

void 				room::pop_obstacle(const model::group::ptr &row)
{
	if (not obstacle_links.empty() and obstacle_links.front().row == row)
	{
		scene::scene::forget(obstacle_links.front().obstacle);
		obstacle_links.pop_front();
	}
}