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
								const model::model::ptr &source
							) :
								blocked_lines(blocked_lines),
								blocked_states(blocked_states)
	{
		instance = model::manager::make_instance(source);
		game_object::render_target(instance);
		enable(false);
	}

							~obstacle() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(obstacle)

protected :

	model::instance::ptr	instance;

private :

	bool					does_trigger_collision = false;

	const line_wrapper		blocked_lines;
	const state_wrapper		blocked_states;
};