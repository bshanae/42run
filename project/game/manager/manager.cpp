#include "manager.h"

#include "game/bonus/bonus.h"
#include "game/bonus/coin.h"
#include "game/bonus/heal.h"
#include "game/bonus/protection.h"

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

	timer_for_font = engine_extensions::timer
	(
		settings().coin_start,
		settings().coin_end,
		settings().coin_duration,
		interpolation_method::cosine
	);

	engine::core::use(timer_for_font);

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

	const int			multiplier = engine::settings().window_scaling.x;

	fonts.intro =  make_shared<font::font>(sources().font, 350 * multiplier, engine::vec3(1.f));
	fonts.victory =  make_shared<font::font>(sources().font, 270 * multiplier, engine::vec3(1.f));
	fonts.defeat =  make_shared<font::font>(sources().font, 270 * multiplier, engine::vec3(1.f));
	fonts.score = make_shared<font::font>(sources().font, 70 * multiplier, engine::vec3(1.f));

	fonts.intro->build_map();
	fonts.victory->build_map();
	fonts.defeat->build_map();
	fonts.score->build_map();

// --------------------	UI : Icons

	auto				build_circle = [](const vec2 &position, string &source)
	{
		auto			result = make_shared<icon::icon>
		(
			position,
			vec2(0.018f / engine::settings().window_ratio, 0.018f),
			source
		);

		global_scene->include(result);
		result->start();

		return (result);
	};

	icons.blue_circles[0] = build_circle(vec2(0.88, 0.33), sources().blue_circle);
	icons.blue_circles[1] = build_circle(vec2(0.92, 0.33), sources().blue_circle);
	icons.blue_circles[2] = build_circle(vec2(0.96, 0.33), sources().blue_circle);

	icons.green_circles[0] = build_circle(vec2(0.88, 0.33), sources().green_circle);
	icons.green_circles[1] = build_circle(vec2(0.92, 0.33), sources().green_circle);
	icons.green_circles[2] = build_circle(vec2(0.96, 0.33), sources().green_circle);

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

	display_health();

// --------------------	Updating values

	const auto			character_range = character->calculate_range();

	static
	shared<room::row>	last_intersected_row;
	shared<room::row>	interesting_row;

	total_row_value += (float)room->rows_swap_counter * row_value;
	total_row_value = min(total_row_value, 21000.f);
	room->rows_swap_counter = 0;
	labels.score->change_text(to_string((int)total_row_value));

	for (auto iterator = room->rows.rbegin(); iterator != room->rows.rend(); ++iterator)
		if ((*iterator)->does_collide(character_range))
		{
			interesting_row = *iterator;
			break ;
		}

	if (timer_for_font.get_state() == engine::interface::timer::state::running)
		fonts.score->change_color(glm::mix(main_font_color, bonus_font_color, timer_for_font.value()));

// --------------------	Test

	if (not interesting_row)
		return ;
	if (last_intersected_row == interesting_row)
		return ;
	if (not interesting_row->does_collide(character_range))
		return;

	last_intersected_row = interesting_row;

// --------------------	Obstacle and bonus


#if DEBUG_VERBOSE
	static int			collision_i;

	cerr << "Collision" << collision_i++ << endl;
#endif

	if (interesting_row->does_collide_with_obstacle(character->current_line, character->current_state))
	{
		character->interact_with_obstacle();
		display_health();
	}
	else if
	(
		auto result = interesting_row->does_collide_with_bonus(character->current_line, character->current_state);
		result.first
	)
		use_bonus(result.second);
}

void					manager::load_scene()
{
	engine::core::use(global_scene);
	engine::core::window_title("42run");

	is_loaded = true;

// -------------------- Models

	room = make_unique<game::room>();
	character = make_unique<game::character>();

	room->start();
	character->start();

	global_scene->include(room);
	global_scene->include(character);

// -------------------- Lights

	global_scene->include
	(
		make_shared<scene::light>
		(
			scene::light::type::ambient,
			vec3(1.f),
			0.7f
		)
	);

	global_scene->include
	(
		make_shared<scene::light>
		(
			scene::light::type::point,
			vec3(0, room->models.room->size().y * 0.8f, 15),
			0.0f,
			vec3(1.0f),
			0.2f
		)
	);
}

void					manager::unload_scene()
{
	character->stop();
	room->stop();
	shared_from_this()->stop();
}

void					manager::display_health()
{
	auto				&current = character->is_protected ? icons.green_circles : icons.blue_circles;
	auto				&other = character->is_protected ? icons.blue_circles : icons.green_circles;

	other[0]->pause(true);
	other[1]->pause(true);
	other[2]->pause(true);

	switch (character->health)
	{
		case 0 :
			current[0]->pause(true);
			current[1]->pause(true);
			current[2]->pause(true);
			break ;

		case 1 :
			current[0]->pause(true);
			current[1]->pause(true);
			current[2]->pause(false);
			break ;

		case 2 :
			current[0]->pause(true);
			current[1]->pause(false);
			current[2]->pause(false);
			break ;

		case 3 :
			current[0]->pause(false);
			current[1]->pause(false);
			current[2]->pause(false);
			break ;

		default :
			warning::raise(warning::id::unexpected_health_value);
	}
}

void					manager::use_bonus(const shared<bonus::bonus> &bonus)
{
	if (dynamic_pointer_cast<bonus::coin>(bonus))
	{
		total_row_value += settings().coin_value;
		timer_for_font.execute();
	}
	else if (dynamic_pointer_cast<bonus::heal>(bonus))
		character->interact_with_heal();
	else if (dynamic_pointer_cast<bonus::protection>(bonus))
		character->interact_with_protection();
	else
		return ;
	bonus->use();
}