#include "room.h"

using namespace					game;

void							room::offset_groups()
{
	row_offset = (vec3){0, 0, -0.99f * models.room->size().z};

	for (int i = 1; i < number_of_rows; i++)
		groups[i]->translate(row_offset * vec3(i));
}