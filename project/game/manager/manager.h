#pragma once

#include "game/namespace.h"

#include "game/room/room.h"
#include "game/character/character.h"

class				game::manager
{
public :

IMPLEMENT_GLOBAL_INITIALIZER(manager)

					manager() = default;
					~manager() = default;

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	room			room;
	character		character;
};
