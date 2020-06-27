#include "room.h"

using namespace		game;

					room::room() : game_object(global().renderer_for_engine)
{
	build_models();
	build_main_instances();
	build_unique_groups();
	prepare_offset();
	offset_groups();
}