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
		instance = make_shared<model_with_mods::instance>(source);
		game_object::render_target(instance);
	}

										~obstacle() override = default;

protected :

	shared<model_with_mods::instance>	instance;

private :

	bool								does_trigger_collision = false;

	const line_wrapper					blocked_lines;
	const state_wrapper					blocked_states;
};