#include "random.h"

int					common::random(const int_range &range)
{
	static bool 	first_call = true;
	static auto		engine = std::default_random_engine();

	if (first_call)
	{
		engine.seed(seed);
		first_call = false;
	}

	auto			distribution = std::uniform_int_distribution(range.lower, range.higher);

	return (distribution(engine));
}

float				common::random(const float_range &range)
{
	static bool 	first_call = true;
	static auto		engine = std::default_random_engine();

	if (first_call)
	{
		engine.seed(seed);
		first_call = false;
	}

	auto			distribution = std::uniform_real_distribution<float>(range.lower, range.higher);

	return (distribution(engine));
}

glm::vec3			common::random(const vec3_range &range)
{
	return
	{
		random(float_range(range.lower.x, range.higher.x)),
		random(float_range(range.lower.y, range.higher.y)),
		random(float_range(range.lower.z, range.higher.z))
	};
}