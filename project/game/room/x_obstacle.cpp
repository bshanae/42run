#include "room.h"

using namespace		game;

void				room::generate_obstacle(const obstacle::obstacle::ptr &obstacle, int row_index)
{
	obstacle_links.emplace_back(obstacle, row_index);
}

void 				room::delete_obstacle(int row_index)
{
	auto			iterator = find_if
	(
		obstacle_links.begin(),
		obstacle_links.end(),
		[&](const obstacle_link &link)
		{
			return (row_index == link.read_row_index());
		}
	);

	if (iterator == obstacle_links.end())
		return ;

	scene::scene::forget(iterator->read_obstacle());
	obstacle_links.erase(iterator);
}