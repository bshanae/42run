#include "manager.h"

using namespace		game;

					manager::manager() : game_object()
{
	room = scene::scene::game_object<game::room>();
	character = scene::scene::game_object<game::character>();

	scene::scene::light(scene::light::type::ambient, vec3(1.f), 0.2f);

	scene::scene::light(
		scene::light::type::point,
		vec3(0, room->models.room->size().y * 0.8f, 15),
		0.0f,
		vec3(1.0f),
		1.0f);

	for (int i = 1; i < 5; i++)
		scene::scene::light(
			scene::light::type::point,
			vec3(0, room->models.room->size().y * 0.65f, i * -35),
			0.1f,
			vec3(1.0f),
			0.3f);
}

void				manager::update()
{
	static int		i;

	for (auto &obstacle : room->obstacle_links)
		if (character->check_collision(obstacle.read_obstacle()))
			std::cerr << "COLLISION" << i++ << std::endl;
}