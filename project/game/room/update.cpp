#include "room.h"

using namespace							game;

#define INCREMENT_TILL(value, limit)	(value + 1) >= limit ? 0 : (value + 1)

void									room::update()
{
	static const vec3					size = models.room->size();

	static int							nearest_index = 0;
	static int							furthest_index = number_of_rows - 1;

	auto								movement = vec3(0, 0, speed * engine::core::time_delta(true));

	auto								nearest_ptr = groups[nearest_index];
	auto								furthest_ptr = groups[furthest_index];

	for (auto &group : groups)
		group->translate(movement);

	for (auto &obstacle_link : obstacle_links)
		obstacle_link->move_to(groups[obstacle_link->read_row_index()]->translation());

	if (nearest_ptr->translation().z > size.z)
	{
//		obstacle_links.erase
//		(
//			remove_if
//			(
//				obstacle_links.begin(),
//				obstacle_links.end(),
//				[&](const obstacle_link::ptr &link)
//				{
//					return (nearest_index == link->read_row_index());
//				}
//			),
//			obstacle_links.end()
//		);

		nearest_ptr->reset_translation();
		nearest_ptr->translate(furthest_ptr->translation());
		nearest_ptr->translate(row_offset);

		furthest_index = nearest_index;
		nearest_index = INCREMENT_TILL(nearest_index, number_of_rows);
	}
}