#pragma once

#include "engine/namespace.h"

class						engine::model::vertex
{
public :
							vertex() = default;
							vertex
							(
								const vec3 &position,
								const vec3 &normal,
								const vec2 &UV
							) :
								position(position),
								normal(normal),
								UV(UV)
							{}

							~vertex() = default;

	vec3					position;
	vec3					normal;
	vec2					UV;

	static constexpr int	bones_limit = SHARED_BONES_IN_VERTEX;

	float					bones_ids[bones_limit] = {0.0f};
	float					bones_weights[bones_limit] = {0.0f};
};