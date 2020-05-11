#pragma once

#include "engine/namespace.h"

class				engine::model::animation
{
public :

	struct
	{
		float		begin;
		float		end;
	}				timestamps;

	float 			speed;

	int				priority;
	bool 			loop;

	explicit		animation(
					float begin_timestamp = 0,
					float end_timestamp = 250,
					float speed = 0.25,
					int priority = 10,
					bool loop = true) :
					timestamps{begin_timestamp, end_timestamp},
					speed(speed),
					priority(priority),
					loop(loop)
					{}
					~animation() = default;
};