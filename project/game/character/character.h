#pragma once

#include "game/namespace.h"

class						game::character : public engine::game_object
{
	friend class			manager;

public :
							character();
							~character() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(character)


	enum class 				line : unsigned int
	{
		left = 0x001,
		middle = 0x010,
		right = 0x100
	};

	enum class				state : unsigned int
	{
		running = 0x01,
		jumping = 0x10
	};

	using					line_wrapper = engine::abstract::bitflags_wrapper<line>;
	using					state_wrapper = engine::abstract::bitflags_wrapper<state>;

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

	line					current_line = line::middle;

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
		switch (line)
		{
			case line::left :
				return (false);

			case line::middle :
				line = line::left;
				return (true);

			case line::right :
				line = line::middle;
				return (true);
		}
	}

	bool					try_go_right(character::line &line)
	{
		switch (line)
		{
			case line::left :
				line = line::middle;
				return (true);

			case line::middle :
				line = line::right;
				return (true);

			case line::right :
				return (false);
		}
	}

	vec3 					current_position = middle_position;
	vec3					target_position = middle_position;
};


