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

IMPLEMENT_GLOBAL_INITIALIZER(manager)

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	shared<game::renderer>	renderer;
	shared<scene::scene>	scene;

	shared<room>			room;
	shared<character>		character;

	void					update() override;
};
