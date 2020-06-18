#pragma once

#include "game/namespace.h"

#include "game/character/character.h"

class							game::obstacle::obstacle : public engine::game_object
{
	friend class				game::manager;

protected :
								obstacle
								(
									const character::line_wrapper &blocked_lines,
									const character::state_wrapper &blocked_states,
									const path &source,
									const model::flags_wrapper &flags
								) :
								blocked_lines(blocked_lines),
								blocked_states(blocked_states)
	{
		model = model::manager::make_model(source, flags);
		instance = model::manager::make_instance(model);

		game_object::render_target(instance);
	}

								~obstacle() override = default;

	model::model::ptr			model;
	model::instance::ptr		instance;

private :

	character::line_wrapper		blocked_lines;
	character::state_wrapper	blocked_states;

	vec3 						position = vec3(0.f);
};