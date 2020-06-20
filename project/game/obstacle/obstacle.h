#pragma once

#include "game/namespace.h"

#include "game/character/character.h"

class								game::obstacle::obstacle : public engine::game_object
{
	friend class					game::manager;
	friend class					game::room;
	friend class					game::character;

public :
									obstacle
									(
										const character::line_wrapper &blocked_lines,
										const character::state_wrapper &blocked_states,
										const float size,
										const path &source,
										const model::flags_wrapper &flags
									) :
										size(size),
										blocked_lines(blocked_lines),
										blocked_states(blocked_states)
	{
		model = model::manager::make_model(source, flags);
	}

									~obstacle() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(obstacle)

protected :

	model::model::ptr				model;

private :

	const character::line_wrapper	blocked_lines;
	const character::state_wrapper	blocked_states;

	const float						size;
};