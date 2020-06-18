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

	void					update() override
	{
		if (not model->is_animation_playing())
			model->animate(animations.run);
	}

	void					callback_functor();
	interface::callback		callback;

	model::model::ptr		model;
	model::instance::ptr	instance;

	struct
	{
		model::animation	run;
		model::animation	jump;
	}						animations;

};


