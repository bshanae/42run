#pragma once

#include "engine/namespace.h"

class				engine::model::animation
{
	friend class	skeleton;

public :
					animation() = default;
					~animation() = default;

	explicit		animation
					(
						float begin_timestamp,
						float end_timestamp,
						float speed = 0.25
					) :
						timestamps{begin_timestamp, end_timestamp},
						speed(speed)
					{}
private :

	struct
	{
		float		begin = 0.f;
		float		end = 0.f;
	}				timestamps;

	float 			speed = 0.f;
};