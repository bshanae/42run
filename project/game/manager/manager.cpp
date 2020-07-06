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

	font_for_intro = make_shared<UI::font::font>
	(
		"project/resources/UI/fonts/HelveticaNeue.ttc",
		120,
		engine::vec3(1, 0, 0)
	);

	font_for_score = make_shared<UI::font::font>
	(
		"project/resources/UI/fonts/HelveticaNeue.ttc",
		40,
		engine::vec3(1, 0, 0)
	);

	font_for_score->build_map();

	for (auto &circle : circles)
	{
		circle = make_shared<UI::icon::icon>(vec2(0.9, 0.5), sources().circle);
		global_scene->include(circle);
		circle->start();
		circle->pause(true);
	}
	show_health();

	score = make_shared<UI::label::label>(vec2(0.98, 0.2), "0", font_for_score, UI::label::alignment::right);

	score->start();
	global_scene->include(score);

	auto				frame = make_shared<UI::frame::frame>
	(
		vec2(0.5f, 0.5f),
		vec2(0.1f, 0.1f),
		vec3(0.2f),
		0.05f,
		vec3(0.15f)
	);

//	frame->start();
//	global_scene->include(frame);
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
			show_game_over();
			break ;

		case 1 :
			circles[0]->pause(false);
			circles[1]->pause(true);
			circles[2]->pause(true);
			circles[0]->change_position(vec2(0.8, 0.5));
			break ;

		case 2 :
			circles[0]->pause(false);
			circles[1]->pause(false);
			circles[2]->pause(true);
			circles[0]->change_position(vec2(0.8, 0.42));
			circles[1]->change_position(vec2(0.8, 0.58));
			break ;

		case 3 :
			circles[0]->pause(false);
			circles[1]->pause(false);
			circles[2]->pause(false);
			circles[0]->change_position(vec2(0.8, 0.35));
			circles[1]->change_position(vec2(0.8, 0.5));
			circles[2]->change_position(vec2(0.8, 0.65));
			break ;

		default :
			warning::raise(warning::id::unexpected_health_value);
	}

}

void					manager::show_game_over()
{}