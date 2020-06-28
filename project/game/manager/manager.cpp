#include "manager.h"

using namespace		game;

					manager::manager() : game_object()
{
	global().scene = make_shared<scene::scene>();
	global().renderer_for_game = make_shared<game::renderer>();
	global().renderer_for_engine = dynamic_pointer_cast<engine::renderer>(global().renderer_for_game);

	engine::core::use(global().scene);

//					Models
	room = make_unique<game::room>();
	character = make_unique<game::character>();

	room->start();
	character->start();

	global().scene->include(room);
	global().scene->include(character);

//					Lights
	global().scene->include(make_shared<scene::light>(scene::light::type::ambient, vec3(1.f), 0.25f));

	global().scene->include
	(
		make_shared<scene::light>
		(
			scene::light::type::point,
			vec3(0, room->models.room->size().y * 0.8f, 15),
			0.0f,
			vec3(1.0f),
			1.0f
		)
	);

	for (int i = 1; i < 5; i++)
		global().scene->include
		(
			make_shared<scene::light>
			(
				scene::light::type::point,
				vec3(0, room->models.room->size().y * 0.65f, i * -35),
				0.1f,
				vec3(1.0f),
				0.3f
			)
		);

	global().renderer_for_game->upload_light_uniforms();
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