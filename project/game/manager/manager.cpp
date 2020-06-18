#include "manager.h"

using namespace		game;

					manager::manager()
{
	room = engine::scene::scene::game_object<game::room>();
	character = engine::scene::scene::game_object<game::character>();

	chair = engine::scene::scene::game_object<game::obstacle::chair>(character::line::middle);

	engine::scene::scene::light(engine::scene::light::type::ambient, vec3(1.f), 0.2f);

	engine::scene::scene::light(
		engine::scene::light::type::point,
		vec3(0, room->models.room->size().y * 0.65f, 15),
		false,
		vec3(1.0f),
		1.f);
}