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

// --------------------	UI : Frames

	frame_for_score = make_shared<frame::frame>
	(
		vec2(0.90f, 0.235f),
		vec2(0.22f, 0.1f),
		vec3(0.2f),
		0.02f,
		vec3(0.12f)
	);

	frame_for_score->start();
	global_scene->include(frame_for_score);

	frame_for_health = make_shared<frame::frame>
	(
		vec2(0.92f, 0.33f),
		vec2(0.18f, 0.08f),
		vec3(0.2f),
		0.02f,
		vec3(0.12f)
	);

	frame_for_health->start();
	global_scene->include(frame_for_health);

// --------------------	UI : Font

	font = make_shared<font::font>(sources().font, 70, engine::vec3(1.f));
	font->build_map();

// --------------------	UI : Icons

	auto				build_circle = [](const vec2 &position)
	{
		auto			result = make_shared<icon::icon>
		(
			position,
			sources().circle
		);

		global_scene->include(result);
		result->start();

		return (result);
	};

	circles[0] = build_circle(vec2(0.88, 0.33));
	circles[1] = build_circle(vec2(0.92, 0.33));
	circles[2] = build_circle(vec2(0.96, 0.33));

// --------------------	UI : Label

	score = make_shared<label::label>(vec2(0.98, 0.2), "0", font, label::alignment::right);

	score->start();
	global_scene->include(score);
}

void					manager::update()
{
	static int			collision_i;
	const auto			character_range = character->calculate_range();

	static
	shared<room::row>	last_intersected_row;
	shared<room::row>	dangerous_row;

	score->change_text(to_string(room->rows_swap_counter));

	for (auto iterator = room->rows.rbegin(); iterator != room->rows.rend(); ++iterator)
		if ((*iterator)->does_intersect(character_range))
		{
			dangerous_row = *iterator;
			break ;
		}

	if (not dangerous_row)
		return ;
	if (last_intersected_row == dangerous_row)
		return ;

	if (not (dangerous_row->blocked_lines() & character->current_line))
		return ;
	if (not (dangerous_row->blocked_states() & character->current_state))
		return ;

	last_intersected_row = dangerous_row;

	cerr << "Collision" << collision_i++ << endl;
	character->health--;
	show_health();
}

void					manager::show_health()
{
	switch (character->health)
	{
		case 0 :
			circles[0]->pause(true);
			circles[1]->pause(true);
			circles[2]->pause(true);
			break ;

		case 1 :
			circles[0]->pause(true);
			circles[1]->pause(true);
			circles[2]->pause(false);
			break ;

		case 2 :
			circles[0]->pause(true);
			circles[1]->pause(false);
			circles[2]->pause(false);
			break ;

		case 3 :
			circles[0]->pause(false);
			circles[1]->pause(false);
			circles[2]->pause(false);
			break ;

		default :
			warning::raise(warning::id::unexpected_health_value);
	}

}

void					manager::show_game_over()
{}