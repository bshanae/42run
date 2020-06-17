#pragma once

#include "game/namespace.h"

class						game::character : public engine::game_object
{
	friend class			manager;

public :
							character();
							~character() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(character)

private :

	void					update() override;

	model::model::ptr		model;
	model::instance::ptr	instance;
};


