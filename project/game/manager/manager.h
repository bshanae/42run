#pragma once

#include "game/namespace.h"

#include "game/renderer/renderer.h"
#include "game/character/character.h"
#include "game/room/room.h"
#include "game/obstacle/chair.h"

class						game::manager :
								public global<game::manager>,
								public game_object::game_object
{
public :
							manager();
							~manager() override = default;

private :

	shared<game::manager>	initializer() override
	{
		auto				result = make_shared<game::manager>();

		result->start();
		return (result);
	};

	shared<room>			room;
	shared<character>		character;

	void					update() override;
};
