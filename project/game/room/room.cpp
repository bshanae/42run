#include "room.h"

using namespace					game;

								room::room()
{
	build_models();
	build_main_instances();
	build_unique_groups();
	offset_groups();
	set_targets();
}