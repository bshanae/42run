#pragma once

#include "engine/namespace.h"

class				engine::animation
{
public :

	string 			name = "unknown";

	float			begin_time = 0.f;
	float			end_time = 0.f;
	float 			speed = 0.25f;

	int				priority = 10;
	bool 			loop = false;

					animation() = default;
					~animation() = default;
};