#pragma once

#include "game/namespace.h"

class						game::obstacle::obstacle : public engine::game_object
{
	friend class			game::manager;
	friend class			game::room;
	friend class			game::character;

public :
							obstacle
							(
								const line_wrapper &blocked_lines,
								const state_wrapper &blocked_states,
								const float size,
								const path &source,
								const model::flags_wrapper &flags
							) :
								size(size),
								blocked_lines(blocked_lines),
								blocked_states(blocked_states)
	{
		model = model::manager::make_model(source, flags);
		instance = model::manager::make_instance(model);

		game_object::render_target(instance);
	}

							~obstacle() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(obstacle)

protected :

	model::model::ptr		model;
	model::instance::ptr	instance;

private :

	const line_wrapper		blocked_lines;
	const state_wrapper		blocked_states;

	const float				size;
};