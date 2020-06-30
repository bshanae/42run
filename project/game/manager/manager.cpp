#include "manager.h"

using namespace			game;

shared<scene::scene>	game::global_scene;

						manager::manager() : game_object()
{
	global_scene = make_shared<scene::scene>();
	engine::core::use(global_scene);

// -------------------- Models

	room = make_unique<game::room>();
	character = make_unique<game::character>();

	room->start();
	character->start();

	global_scene->include(room);
	global_scene->include(character);

// -------------------- Lights

	global_scene->include(make_shared<scene::light>(scene::light::type::ambient, vec3(1.f), 0.25f));

	global_scene->include
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
		global_scene->include
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

// --------------------	UI

	auto				font = make_shared<UI::font::font>
	(
		"./project/resources/UI/fonts/HelveticaNeue.ttc",
		40,
		vec3(1, 0, 0)
	);

	auto				label = make_shared<UI::label::label>
	(
		ivec2(100, 100),
		"Hello",
		font
	);

	label->start();
	global_scene->include(label);
}

void					manager::update()
{
	static int			collision_i;
	const auto			character_range = character->calculate_range();

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