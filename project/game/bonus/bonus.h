#pragma once

#include "game/namespace.h"

#include "game/renderer/renderer.h"

class									game::bonus::bonus : public engine::game_object::game_object
{
	friend class						game::manager;
	friend class						game::room;
	friend class						game::character;

public :
										bonus
										(
											const line_wrapper &blocked_lines,
											const state_wrapper &blocked_states,
											const shared<model::model> &source
										) :
											game_object(tag<game::renderer>()),
											used_lines(blocked_lines),
											used_states(blocked_states)
	{
		instance = make_shared<engine_extensions::instance>(source);
		game_object::render_target(instance);
	}
										~bonus() override = default;

	void								use()
	{
		pause(true);
		was_used = true;
	}

	virtual void						pause(bool state) override
	{
		if (not was_used)
			game_object::pause(state);
	}

protected :

	shared<engine_extensions::instance>	instance;

private :

	bool								was_used = false;

	const line_wrapper					used_lines;
	const state_wrapper					used_states;
};