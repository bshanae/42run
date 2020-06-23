#include "room.h"

using namespace					game;

								room::room()
{
	build_models();
	build_main_instances();
	build_unique_groups();
	prepare_offset();
	offset_groups();
}