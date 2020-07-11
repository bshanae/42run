#include "room.h"

using namespace		game;

					room::room() : game_object(tag<game::renderer>())
{
	build_models();
	build_instances();
	build_groups();
	prepare_offset();
	offset_groups();
}