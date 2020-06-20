#include "manager.h"

using namespace		game;

					manager::manager()
{
	room = engine::scene::scene::game_object<game::room>();
	character = engine::scene::scene::game_object<game::character>();

	engine::scene::scene::light(engine::scene::light::type::ambient, vec3(1.f), 0.2f);

	engine::scene::scene::light(
		engine::scene::light::type::point,
		vec3(0, room->models.room->size().y * 0.8f, 15),
		0.0f,
		vec3(1.0f),
		1.0f);

	for (int i = 1; i < 5; i++)
		engine::scene::scene::light(
			engine::scene::light::type::point,
			vec3(0, room->models.room->size().y * 0.65f, i * -35),
			0.1f,
			vec3(1.0f),
			0.3f);
}