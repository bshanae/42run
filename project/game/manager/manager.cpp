#include "manager.h"

using namespace		game;

vec3				rotate(const vec3 &source, float x, float y, float z)
{
	const auto		source_vec4 = vec4(source, 0);
	const auto		rotation = glm::eulerAngleXYZ(glm::radians(x), glm::radians(y), glm::radians(z));

	return (rotation * source_vec4);
}

					manager::manager()
{
	engine::scene::scene::light(engine::scene::light::type::directional, rotate(vec3(0, 0, -1), -30, 0, 0), vec3(1.f), 0.5f);
	engine::scene::scene::light(engine::scene::light::type::directional, rotate(vec3(0, 0, -1), 15, 0, 0), vec3(1.f), 0.5f);

	engine::scene::scene::light(engine::scene::light::type::point, vec3(-20, 10, 0), vec3(1.0f), 1.f);
	engine::scene::scene::light(engine::scene::light::type::point, vec3(-10, 10, 0), vec3(1.0f), 1.f);
	engine::scene::scene::light(engine::scene::light::type::point, vec3(10, 10, 0), vec3(1.0f), 1.f);
	engine::scene::scene::light(engine::scene::light::type::point, vec3(20, 10, 0), vec3(1.0f), 1.f);
}