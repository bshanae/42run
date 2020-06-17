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
		ambient = SHARED_LIGHT_TYPE_AMBIENT,
		directional = SHARED_LIGHT_TYPE_DIRECTIONAL,
		point = SHARED_LIGHT_TYPE_POINT,
		projector = SHARED_LIGHT_TYPE_PROJECTOR
	};

					~light() = default;
private :
					light(
					enum type type,
					const vec3 &color,
					float power) :
					type(type),
					color(color),
					power(power)
	{
		if (type != type::ambient)
			error::raise(error::id::light_bad_input);
	}
					light(
					enum type type,
					const vec3 &direction,
					const vec3 &color,
					float power) :
					type(type),
					color(color),
					power(power)
	{
		if (type != type::directional)
			error::raise(error::id::light_bad_input);

		parameter_a = direction;
	}

					light(
					enum type type,
					const vec3 &position,
					bool use_attenuation,
					const vec3 &color,
					float power) :
					type(type),
					color(color),
					power(power)
	{
		if (type != type::point)
			error::raise(error::id::light_bad_input);

		parameter_a = position;
		parameter_c = use_attenuation ? 1.f : 0.f;
	}

					light(
					enum type type,
					const vec3 &position,
					const vec3 &direction,
					float cut_off,
					float outer_cut_off,
					const vec3 &color,
					float power) :
					type(type),
					color(color),
					power(power)
	{
		if (type != type::projector)
			error::raise(error::id::light_bad_input);

		parameter_a = position;
		parameter_b = direction;
		parameter_c = cos(radians(cut_off));
		parameter_d = cos(radians(outer_cut_off));
	}

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(light)

	const enum type	type;

	vec3			parameter_a;
	vec3			parameter_b;
	float			parameter_c;
	float			parameter_d;

	vec3			color = vec3(1.f);
	float			power = 1.f;
};