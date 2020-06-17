#include "manager.h"

using namespace		game;

					manager::manager()
{
	engine::scene::scene::light(engine::scene::light::type::ambient, vec3(1.f), 0.15f);

	engine::scene::scene::light(
		engine::scene::light::type::point,
		vec3(0, room.models.room->size().y * 0.65f, 15),
		false,
		vec3(1.0f),
		1.f);
}