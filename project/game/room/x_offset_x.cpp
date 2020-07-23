#include "room.h"

#include "game/engine_extensions/group.h"

using namespace					game;

void							room::prepare_offset()
{
	row_offset = (vec3){0, 0, -0.99f * models.room->size().z};
	row_range = float_range(-row_offset.z / 2.f, +row_offset.z / 2.f);
}

void							room::offset_groups()
{
	for (int i = 1; i < number_of_rows; i++)
		rows[i]->read_group()->translate(row_offset * vec3(i));
}