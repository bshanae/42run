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
//	engine::scene::scene::light(engine::scene::light::type::directional, rotate(vec3(0, 0, -1), -30, 0, 0), vec3(1.f), 0.5f);
//	engine::scene::scene::light(engine::scene::light::type::directional, rotate(vec3(0, 0, -1), 15, 0, 0), vec3(1.f), 0.5f);

	vec3			block_left;
	vec3			block_fourth;
	vec3 			block_interval;

	vec3			light_position[3];

	block_left = room.models.room->min();
	block_left.y = room.models.room->size().y * 0.65f;
	block_left.z += room.models.room->size().z * 0.65f;

	block_fourth.x = room.models.room->size().x / 4.f;

	block_interval.z = -1.f * room.models.room->size().z;

	for (int i = 0; i < 3; i++)
		light_position[i] = block_left + block_fourth * vec3(i + 1);

	light_position[0].x -= block_fourth.x / 2;
	light_position[1].x += block_fourth.x / 2;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			engine::scene::scene::light(
				engine::scene::light::type::projector,
				light_position[j] + block_interval * vec3(i),
				vec3(0, -1, 0),
				60.f,
				80.f,
				vec3(1.0f),
				3.f);

//	engine::scene::scene::light(
//		engine::scene::light::type::projector,
//		vec3(0, 20, -10),
//		vec3(0, -1, 0),
//		60.f,
//		80.f,
//		vec3(1.f),
//		5.f);
}