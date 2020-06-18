#pragma once

#include "game/namespace.h"

#include "game/obstacle/obstacle.h"

class				game::obstacle::chair : public game::obstacle::obstacle
{
	friend class	game::manager;

public :

					chair(character::line line) :
					obstacle
					(
						line,
						character::state::running,
						sources().chair,
						model::flags::analyze
					)
					{}
					~chair() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(chair)
};