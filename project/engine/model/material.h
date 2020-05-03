#pragma once

#include "engine/namespace.h"

#include "engine/model/texture.h"

class						engine::material
{
public :
							material() = default;
							~material() = default;
	struct
	{
		vec3 				ambient = vec3(0.f, 0.f, 0.f);
		vec3 				diffuse = vec3(1.f, 1.f, 1.f);
		vec3 				specular = vec3(0.f, 0.f, 0.f);
	}						colors;

	struct
	{
		optional<texture>	diffuse;
		optional<texture>	specular;
	}						textures;
};
