#pragma once

#include "common/range/range.h"

#include <random>

namespace			common
{
	inline int		seed = 1;

	float			random(const float_range &range);
	glm::vec3		random(const vec3_range &range);
}