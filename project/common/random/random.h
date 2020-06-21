#pragma once

#include "common/range/range.h"

#include <random>

namespace			common
{
	inline int		seed = 1;

	int				random(const int_range &range);
	float			random(const float_range &range);
	glm::vec3		random(const vec3_range &range);
}