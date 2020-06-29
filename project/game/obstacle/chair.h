#pragma once

#include "game/namespace.h"

#include "game/obstacle/obstacle.h"

class								game::obstacle::chair : public game::obstacle::obstacle
{
	friend class					game::manager;

public :
									chair(line line) : obstacle(line, state::running, receive_model())
	{
		vec3						position = vec3(0.f);
		vec3						rotation = vec3(0.f);

		if (line == line::left)
			position.x = -constants::distance_between_lines;
		else if (line == line::right)
			position.x = +constants::distance_between_lines;

		position.y = receive_model()->size().y / 2.f;
		rotation.y = random(int_range(0, 360));

		instance->translate(position);
		instance->rotate(rotation);
	}
									~chair() override = default;

private :

	static shared<model::model>		receive_model()
	{
		static shared<model::model>	model;

		if (not model)
			model = model::manager::make(sources().chair, model::flag::center);
		return (model);
	}
};