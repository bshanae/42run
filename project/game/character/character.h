#pragma once

#include "game/namespace.h"

#include "game/obstacle/obstacle.h"

class						game::character : public engine::game_object
{
	friend class			manager;

public :
							character();
							~character() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(character)

private :

	void					update() override;

	float_range				calculate_range() const;

	void					callback_functor();
	interface::callback		callback;

	model::model::ptr		model;
	model::instance::ptr	instance;

	static constexpr float	size = 5.f;

	struct
	{
		model::animation	run;
		model::animation	jump;
	}						animations;

//							Speed of changing row action
	static constexpr float	speed = 0.55f;

	line					current_line = line::middle;
	state					current_state = state::running;

	void					update_state()
	{
		const float			time = model->current_animation_timestamp();

		auto				is_time_in_range = [time](float min, float max)
		{
			return (time >= min and time <= max);
		};

		if (is_time_in_range(28, 44))
			current_state = state::jumping;
		else
			current_state = state::running;
	}

	const vec3				middle_position = vec3(0.f);
	const vec3				left_position = middle_position - vec3(constants::distance_between_lines, 0, 0);
	const vec3				right_position = middle_position + vec3(constants::distance_between_lines, 0, 0);

	const vec3				&position_for_line(enum line line)
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

	bool					try_go_left(enum line &line)
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

	bool					try_go_right(enum line &line)
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


