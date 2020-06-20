#pragma once

#include "engine/namespace.h"

class					engine::scene::light
{
	friend class		engine::scene::scene;
	friend class		engine::renderer;

public :

	enum class			type : int
	{
		ambient = SHARED_LIGHT_TYPE_AMBIENT,
		directional = SHARED_LIGHT_TYPE_DIRECTIONAL,
		point = SHARED_LIGHT_TYPE_POINT,
		projector = SHARED_LIGHT_TYPE_PROJECTOR
	};

						~light() = default;
private :
						light
						(
							enum type type,
							const vec3 &color,
							float power
						) :
							type(type),
							color(color),
							power(power)
	{
		if (type != type::ambient)
			error::raise(error::id::light_bad_input);
	}
						light
						(
							enum type type,
							const vec3 &direction,
							const vec3 &color,
							float power
						) :
							type(type),
							color(color),
							power(power)
	{
		if (type != type::directional)
			error::raise(error::id::light_bad_input);

		parameter_a = direction;
	}

						light
						(
							enum type type,
							const vec3 &position,
							float attenuation_factor,
							const vec3 &color,
							float power
						) :
							type(type),
							color(color),
							power(power)
	{
		if (type != type::point)
			error::raise(error::id::light_bad_input);

		parameter_a = position;

		auto			lower = attenuation_map.lower_bound(attenuation_factor);
		auto			upper = attenuation_map.upper_bound(attenuation_factor);

		auto			result = attenuation_map.end();

		if (abs(lower->first - attenuation_factor) <= abs(upper->first - attenuation_factor))
			result = lower;
		else
			result = upper;

		parameter_c = result->second.first;
		parameter_d = result->second.second;
	}

						light
						(
							enum type type,
							const vec3 &position,
							const vec3 &direction,
							float cut_off,
							float outer_cut_off,
							const vec3 &color,
							float power
						) :
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

	const enum type		type;

	vec3				parameter_a;
	vec3				parameter_b;
	float				parameter_c;
	float				parameter_d;

	vec3				color = vec3(1.f);
	float				power = 1.f;

	using				map_type = map<float, pair<float, float>>;

	static
	inline
	const
	map_type			attenuation_map =
	{
		{1.f,			{0.7,		1.8}},
		{0.909f,		{0.35,		0.44}},
		{0.818f,		{0.22,		0.20}},
		{0.727f,		{0.14,		0.07}},
		{0.636f,		{0.09,		0.032}},
		{0.545f,		{0.07,		0.017}},
		{0.454f,		{0.045,		0.0075}},
		{0.363f,		{0.027,		0.0028}},
		{0.272f,		{0.022,		0.0019}},
		{0.181f,		{0.014,		0.0007}},
		{0.090f,		{0.007,		0.0002}},
		{0.000f,		{0.0014,	0.000007}}
	};
};