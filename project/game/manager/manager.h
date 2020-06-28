#pragma once

#include "game/namespace.h"

#include "game/renderer/renderer.h"
#include "game/character/character.h"
#include "game/room/room.h"
#include "game/obstacle/chair.h"

class						game::manager : public game_object::game_object
{
public :
							manager();
							~manager() override = default;

START_GLOBAL_INITIALIZER(manager)
	instance()->start();
FINISH_GLOBAL_INITIALIZER

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	shared<room>			room;
	shared<character>		character;

	void					update() override;
};
