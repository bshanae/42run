#pragma once

#include "game/namespace.h"

class						game::character : public engine::game_object
{
	friend class			manager;

public :
							character();
							~character() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(character)

private :

	void					update() override;

	void					callback_functor();
	interface::callback		callback;

	model::model::ptr		model;
	model::instance::ptr	instance;

	struct
	{
		model::animation	run;
		model::animation	jump;
	}						animations;

//							Distance to neighbor line
	static constexpr float	offset = 6.f;
//							Speed of changing row action
	static constexpr float	speed = 0.55f;

	enum class 				line : int
	{
		left,
		middle,
		right
	}						current_line = line::middle;

	const vec3				middle_position = vec3(0.f);
	const vec3				left_position = middle_position - vec3(offset, 0, 0);
	const vec3				right_position = middle_position + vec3(offset, 0, 0);

	const vec3				&position_for_line(character::line line)
	{
		switch (line)
		{
			case line::middle :
				return (middle_position);

			case line::left :
				return (left_position);

			case line::right :
				return (right_position);
		}
	}

	bool					try_go_left(character::line &line)
	{
		if (line != line::left)
		{
			line = static_cast<character::line>(static_cast<int>(line) - 1);
			return (true);
		}

		return (false);
	}

	bool					try_go_right(character::line &line)
	{
		if (line != line::right)
		{
			line = static_cast<character::line>(static_cast<int>(line) + 1);
			return (true);
		}

		return (false);
	}

	vec3 					current_position = middle_position;
	vec3					target_position = middle_position;
};


