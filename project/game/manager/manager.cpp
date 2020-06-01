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
//	engine::renderer::light(
//		engine::renderer::light_type::directional,
//		rotate(vec3(0, -1, 0), 15, 0, 0),
//		vec3(0.1));
//	engine::renderer::light(
//		engine::renderer::light_type::directional,
//		rotate(vec3(0, -1, 0), -45, 0, 0),
//		vec3(0.1));
	engine::renderer::light(engine::renderer::light_type::point, vec3(0, 10, -50), vec3(0.8f));
}