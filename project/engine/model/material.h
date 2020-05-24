#pragma once

#include "engine/namespace.h"

#include "engine/abstract/pointer.h"
#include "engine/model/texture.h"

class						engine::model::material
{
public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(material)

							material() = default;
							~material() = default;
	struct
	{
		vec3 				ambient = vec3(0.f, 0.f, 0.f);
		vec3 				diffuse = vec3(1.f, 1.f, 1.f);
		vec3 				specular = vec3(0.f, 0.f, 0.f);
		float				alpha = 1.f;
	}						unite;

	struct
	{
		texture::ptr		ambient;
		texture::ptr		diffuse;
		texture::ptr		specular;
	}						textures;
};
