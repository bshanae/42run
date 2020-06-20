#pragma once

#include "game/namespace.h"

#include "game/room/room.h"
#include "game/character/character.h"
#include "game/obstacle/chair.h"

class						game::manager
{
public :

IMPLEMENT_GLOBAL_INITIALIZER(manager)

							manager();
							~manager() = default;
private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	room::ptr				room;
	character::ptr			character;
};
