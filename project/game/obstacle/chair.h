#pragma once

#include "game/namespace.h"

#include "game/obstacle/obstacle.h"

class				game::obstacle::chair : public game::obstacle::obstacle
{
	friend class	game::manager;

public :
					chair(line line) :
					obstacle
					(
						line,
						state::running,
						3.f,
						sources().chair,
						model::flags::center
					)
	{
		instance->translate(vec3(0, model->size().y / 2.f, 0));
		instance->rotate(vec3(0, 180, 0));
	}
					~chair() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(chair)
};