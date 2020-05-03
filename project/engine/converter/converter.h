#pragma once

#include "engine/namespace.h"

namespace				engine::converter
{
	[[nodiscard]] auto	to_path(const aiString &source)
	{
		return (path(source.C_Str()));
	}

	[[nodiscard]] auto	to_glm(const aiColor3D &source)
	{
		return (vec3(source.r, source.g, source.b));
	}

	[[nodiscard]] auto	to_glm(const aiVector3D &source)
	{
		return (vec3(source.x, source.y, source.z));
	}

	[[nodiscard]] auto	to_glm(const aiVector2D &source)
	{
		return (vec2(source.x, source.y));
	}
};