#pragma once

#include "engine/namespace.h"

class				engine::scene::light
{
	friend class	engine::scene::scene;
	friend class	engine::renderer;

public :

	enum class		type : int
	{
		empty = SHARED_LIGHT_TYPE_EMPTY,
		directional = SHARED_LIGHT_TYPE_DIRECTIONAL,
		point = SHARED_LIGHT_TYPE_POINT
	};
					light() = default;
					~light() = default;
private :

					light(
					enum type type,
					vec3 data,
					vec3 color,
					float power) :
					type(type),
					data(data),
					color(color),
					power(power)
					{}

	enum type		type = type::empty;
	vec3			data = vec3(0.f);
	vec3			color = vec3(1.f);
	float			power = 1.f;
};