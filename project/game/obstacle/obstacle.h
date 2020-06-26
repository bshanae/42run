#pragma once

#include "game/namespace.h"

class						game::obstacle::obstacle : public engine::game_object::game_object
{
	friend class			game::manager;
	friend class			game::room;
	friend class			game::character;

public :
							obstacle
							(
								const shared<engine::renderer> &renderer,
								const line_wrapper &blocked_lines,
								const state_wrapper &blocked_states,
								const shared<model::model> &source
							) :
								game_object(renderer),
								blocked_lines(blocked_lines),
								blocked_states(blocked_states)
	{
		instance = make_shared<model::instance>(source);
		game_object::render_target(instance);
		is_enabled = false;
	}

							~obstacle() override = default;

protected :

	shared<model::instance>	instance;

private :

	bool					does_trigger_collision = false;

	const line_wrapper		blocked_lines;
	const state_wrapper		blocked_states;
};