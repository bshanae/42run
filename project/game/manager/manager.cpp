#include "manager.h"

using namespace			game;

shared<scene::scene>	game::global_scene;

						manager::manager() : game_object()
{
	scenes.intro = make_shared<scene::scene>();
	scenes.victory = make_shared<scene::scene>();
	scenes.defeat = make_shared<scene::scene>();
	global_scene = make_shared<scene::scene>();

	scenes.intro->background(settings().title_scene_background);
	scenes.victory->background(settings().title_scene_background);
	scenes.defeat->background(settings().title_scene_background);
	global_scene->background(settings().game_scene_background);

	engine::core::use(scenes.intro);

// --------------------	UI : Frames

	frames.score = make_shared<frame::frame>
	(
		vec2(0.90f, 0.235f),
		vec2(0.22f, 0.1f),
		vec3(0.2f),
		0.02f,
		vec3(0.12f)
	);

	frames.score->start();
	global_scene->include(frames.score);

	frames.health = make_shared<frame::frame>
	(
		vec2(0.92f, 0.33f),
		vec2(0.18f, 0.08f),
		vec3(0.2f),
		0.02f,
		vec3(0.12f)
	);

	frames.health->start();
	global_scene->include(frames.health);

// --------------------	UI : Font

	fonts.intro =  make_shared<font::font>(sources().font, 350, engine::vec3(1.f));
	fonts.victory =  make_shared<font::font>(sources().font, 270, engine::vec3(1.f));
	fonts.defeat =  make_shared<font::font>(sources().font, 270, engine::vec3(1.f));
	fonts.score = make_shared<font::font>(sources().font, 70, engine::vec3(1.f));

	fonts.intro->build_map();
	fonts.victory->build_map();
	fonts.defeat->build_map();
	fonts.score->build_map();

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

	icons.circles[0] = build_circle(vec2(0.88, 0.33));
	icons.circles[1] = build_circle(vec2(0.92, 0.33));
	icons.circles[2] = build_circle(vec2(0.96, 0.33));

// --------------------	UI : Label

	labels.intro = make_shared<label::label>(vec2(0.5, 0.5), "42run", fonts.intro);
	labels.victory = make_shared<label::label>(vec2(0.5, 0.5), "You won!", fonts.victory);
	labels.defeat = make_shared<label::label>(vec2(0.5, 0.5), "You lost.", fonts.defeat);
	labels.score = make_shared<label::label>(vec2(0.98, 0.235f), "0", fonts.score, label::alignment::right);

	labels.intro->start();
	labels.victory->start();
	labels.defeat->start();
	labels.score->start();

	scenes.intro->include(labels.intro);
	scenes.victory->include(labels.victory);
	scenes.defeat->include(labels.defeat);
	global_scene->include(labels.score);
}

void					manager::update()
{
// --------------------	Scene

	if (not is_loaded)
		load_scene();

	if (total_row_value == 21000.f)
	{
		engine::core::use(scenes.victory);
		unload_scene();
	}
	else if (character->health == 0)
	{
		engine::core::use(scenes.defeat);
		unload_scene();
	}

// --------------------	Updating values

	const auto			character_range = character->calculate_range();

	static
	shared<room::row>	last_intersected_row;
	shared<room::row>	dangerous_row;

	total_row_value += (float)room->rows_swap_counter * row_value * row_value_factor;
	total_row_value = min(total_row_value, 21000.f);
	room->rows_swap_counter = 0;
	labels.score->change_text(to_string((int)total_row_value));

	if (row_value_factor < settings().maximum_row_value_factor)
		row_value_factor *= (1.f + settings().increase_of_row_value);

	for (auto iterator = room->rows.rbegin(); iterator != room->rows.rend(); ++iterator)
		if ((*iterator)->does_intersect(character_range))
		{
			dangerous_row = *iterator;
			break ;
		}

// --------------------	Intersection

	if (not dangerous_row)
		return ;
	if (last_intersected_row == dangerous_row)
		return ;

	if (not (dangerous_row->blocked_lines() & character->current_line))
		return ;
	if (not (dangerous_row->blocked_states() & character->current_state))
		return ;

// --------------------	Hit

	last_intersected_row = dangerous_row;

#if DEBUG
	static int			collision_i;

	cerr << "Collision" << collision_i++ << endl;
#endif

	character->get_hit();
	display_health();
}

void					manager::load_scene()
{
	engine::core::use(global_scene);
	is_loaded = true;

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
}

void					manager::display_health()
{
	switch (character->health)
	{
		case 0 :
			icons.circles[0]->pause(true);
			icons.circles[1]->pause(true);
			icons.circles[2]->pause(true);
			break ;

		case 1 :
			icons.circles[0]->pause(true);
			icons.circles[1]->pause(true);
			icons.circles[2]->pause(false);
			break ;

		case 2 :
			icons.circles[0]->pause(true);
			icons.circles[1]->pause(false);
			icons.circles[2]->pause(false);
			break ;

		case 3 :
			icons.circles[0]->pause(false);
			icons.circles[1]->pause(false);
			icons.circles[2]->pause(false);
			break ;

		default :
			warning::raise(warning::id::unexpected_health_value);
	}
}

void					manager::unload_scene()
{
	character->stop();
	room->stop();
	shared_from_this()->stop();
}