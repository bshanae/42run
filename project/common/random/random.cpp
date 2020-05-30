#include "random.h"

float										common::random(const float_range &range)
{
	static std::default_random_engine		twister;
	std::uniform_real_distribution<float>	distribution(range.lower, range.higher);

	return distribution(twister);
}

glm::vec3									common::random(const vec3_range &range)
{
	return
		{
			random({range.lower.x, range.higher.x}),
			random({range.lower.y, range.higher.y}),
			random({range.lower.z, range.higher.z})
		};
}