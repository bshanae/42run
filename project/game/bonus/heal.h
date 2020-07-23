#pragma once

#include "game/namespace.h"

#include "game/bonus/bonus.h"

class							game::bonus::heal : public game::bonus::bonus
{
	friend class				game::manager;

public :

	explicit					heal(line line) : bonus(line, state::running, global_model())
	{
		vec3					position = vec3(0.f);
		vec3					rotation = vec3(0.f);

		if (line == line::left)
			position.x = -constants::distance_between_lines;
		else if (line == line::right)
			position.x = +constants::distance_between_lines;

		position.y = 10 + random(float_range(-0.4f, 0.4f));

		instance->translate(position);
		instance->rotate(rotation);
		instance->hollow(true);
	}
								~heal() override = default;

private :

	static
	shared<model::model>		global_model()
	{
		static
		shared<model::model>	model;

		if (not model)
			model = make_shared<model::model>(sources().bonus_heal, model::flag::center);
		return (model);
	}
};