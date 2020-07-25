#include "converter.h"

using namespace		engine;

string				converter::to_string(const aiString &source)
{
	return (string(source.data));
}

vec3				converter::to_glm(const aiColor3D &source)
{
	return (vec3(source.r, source.g, source.b));
}

vec2				converter::to_glm(const aiVector2D &source)
{
	return (vec2(source.x, source.y));
}

vec3				converter::to_glm(const aiVector3D &source)
{
	return (vec3(source.x, source.y, source.z));
}

quat				converter::to_glm(const  aiQuaternion &source)
{
	return (quat(source.w, source.x, source.y, source.z));
}

mat4				converter::to_glm(const aiMatrix4x4 &source)
{
	mat4			target;

	target[0][0] = source.a1;
	target[0][1] = source.b1;
	target[0][2] = source.c1;
	target[0][3] = source.d1;

	target[1][0] = source.a2;
	target[1][1] = source.b2;
	target[1][2] = source.c2;
	target[1][3] = source.d2;

	target[2][0] = source.a3;
	target[2][1] = source.b3;
	target[2][2] = source.c3;
	target[2][3] = source.d3;

	target[3][0] = source.a4;
	target[3][1] = source.b4;
	target[3][2] = source.c4;
	target[3][3] = source.d4;

	return (target);
}

aiMatrix4x4			converter::to_assimp(const mat4 &source)
{
	return (aiMatrix4x4
	(
		source[0][0], source[1][0], source[2][0], source[3][0],
		source[0][1], source[1][1], source[2][1], source[3][1],
		source[0][2], source[1][2], source[2][2], source[3][2],
		source[0][3], source[1][3], source[2][3], source[3][3]
	));
}

ivec2				converter::to_absolute(const vec2 &source)
{
	auto			window_size = engine::settings().window_size;

	return {window_size.x * source.x, window_size.y * source.y};
}

vec2				converter::to_relative(const vec2 &source)
{
	auto			window_size = engine::settings().window_size;

	return {source.x / window_size.x, source.y / window_size.y};
}