#include "room.h"

using namespace					game;

void							room::set_targets()
{
	for (const auto &group : groups)
		game_object::target(group);
}
