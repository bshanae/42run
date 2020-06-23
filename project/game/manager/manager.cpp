#include "manager.h"

using namespace		game;

					manager::manager() : game_object()
{
	room = scene::scene::game_object<game::room>();
	character = scene::scene::game_object<game::character>();

	scene::scene::light(scene::light::type::ambient, vec3(1.f), 0.25f);

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
	static int		collision_i;
	const auto		character_range = character->calculate_range();

	for (int i = room::dangerous_rows_for_character.lower; i <= room::dangerous_rows_for_character.higher; i++)
	{
		if (not (room->rows[i].blocked_lines() & character->current_line))
			continue ;
		if (not (room->rows[i].blocked_states() & character->current_state))
			continue ;
		if (not room->rows[i].does_intersects(character_range))
			continue ;

		cerr << "COLLISION" << collision_i++ << endl;
	}
}