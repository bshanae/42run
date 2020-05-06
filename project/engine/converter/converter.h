#pragma once

#include "engine/namespace.h"

namespace						engine::converter
{
	[[nodiscard]] string		to_string(const aiString &source);
	[[nodiscard]] path			to_path(const aiString &source);

	[[nodiscard]] vec3			to_glm(const aiColor3D &source);
	[[nodiscard]] vec2			to_glm(const aiVector2D &source);
	[[nodiscard]] vec3			to_glm(const aiVector3D &source);
	[[nodiscard]] quat			to_glm(const  aiQuaternion &source);
	[[nodiscard]] mat4			to_glm(const aiMatrix4x4 &source);

	[[nodiscard]] aiMatrix4x4	to_assimp(const mat4 &source);
}