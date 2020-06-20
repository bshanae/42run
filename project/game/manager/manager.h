#pragma once

#include "game/namespace.h"

#include "game/room/room.h"
#include "game/character/character.h"
#include "game/obstacle/chair.h"

class						game::manager : public game_object
{
public :
							manager();
							~manager() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(manager)

START_GLOBAL_CUSTOM_INITIALIZER(manager)
	instance(false) = scene::scene::game_object<manager>();
FINISH_GLOBAL_CUSTOM_INITIALIZER

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)


	room::ptr				room;
	character::ptr			character;

	void					update() override;
};
