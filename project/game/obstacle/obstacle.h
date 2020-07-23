#pragma once

#include "game/namespace.h"

#include "game/renderer/renderer.h"

class									game::obstacle::obstacle : public engine::game_object::game_object
{
	friend class						game::manager;
	friend class						game::room;
	friend class						game::character;

public :
										obstacle
										(
											const line_wrapper &blocked_lines,
											const state_wrapper &blocked_states,
											const shared<model::model> &source
										) :
											game_object(tag<game::renderer>()),
											blocked_lines(blocked_lines),
											blocked_states(blocked_states)
	{
		instance = make_shared<engine_extensions::instance>(source);
		game_object::render_target(instance);
	}

										~obstacle() override = default;

protected :

	shared<engine_extensions::instance>	instance;

private :

	const line_wrapper					blocked_lines;
	const state_wrapper					blocked_states;
};