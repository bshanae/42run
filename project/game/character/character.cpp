#include "character.h"

#include "game/renderer/renderer.h"

using namespace		game;

					character::character() : game_object(tag<game::renderer>())
{
	auto			flags = model::flag::triangulate;

	common::warning::is_muted = true;
	model = make_shared<model::model>(sources().character, flags);
	common::warning::is_muted = false;

	instance = make_shared<model_with_mods::instance>(model);

	instance->scale(0.085f);
	instance->rotate(engine::vec3(0, 180, 0));
	instance->color_mix_factor(0.0f);
	instance->color_mix_color(settings().hit_effect_color);

	animations.run = model::animation(1, 19, 1.);
	animations.jump = model::animation(20, 63, 0.7);

	model->animate(animations.run);

	game_object::render_target(instance);
	game_object::animation_target(model);

	callback = interface::callback(interface::event::type::key_press, &character::callback_functor, this);
	timer = interface::timer(game::settings().hit_effect_duration);

	engine::core::use(callback);
	engine::core::use(timer);
}

void				character::update()
{
	if (not model->is_animation_playing())
		model->animate(animations.run);

	update_state();

	if (current_position != target_position)
	{
		current_position = lerp(current_position, target_position, speed * speed_factor);

		instance->reset_translation();
		instance->translate(current_position);
	}

//					Update values
	if (speed_factor > settings().maximum_character_speed_factor)
		speed_factor *= (1.f + settings().increase_of_character_speed);
	if (color_mix_value < M_PI_2)
	{
		instance->color_mix_factor(cos(color_mix_value) * settings().hit_effect_factor);
		color_mix_value += settings().hit_effect_fade_out_step * (float)M_PI_2;
	}
	else
		instance->color_mix_state(false);

//					Update hollow state
	if (timer.has_finished())
		instance->hollow(false);
}

void				character::update_state()
{
	const float		time = model->current_animation_timestamp();

	if (time >= 28 and time <= 38)
		current_state = state::jumping;
	else
		current_state = state::running;
}

float_range 		character::calculate_range() const
{
	return {current_position.z - size / 2.f, current_position.z + size / 2.f};
}

void				character::callback_functor()
{
	auto			key = engine::core::receive_event().read_key();

	switch (key)
	{
		case engine::interface::key::space :
			model->animate(animations.jump);
			break;

		case engine::interface::key::number_1 :
		case engine::interface::key::left :
		case engine::interface::key::letter_a :
			if (current_state == state::running and try_go_left(current_line))
				target_position = position_for_line(current_line);
			break ;

		case engine::interface::key::number_2 :
		case engine::interface::key::right :
		case engine::interface::key::letter_d :
			if (current_state == state::running and try_go_right(current_line))
				target_position = position_for_line(current_line);
			break ;

		default :
			break ;
	}
}

const vec3			&character::position_for_line(enum line line)
{
	switch (line)
	{
		case line::middle :
			return (middle_position);

		case line::left :
			return (left_position);

		case line::right :
			return (right_position);
	}
}

bool				character::try_go_left(enum line &line)
{
	switch (line)
	{
		case line::left :
			return (false);

		case line::middle :
			line = line::left;
			return (true);

		case line::right :
			line = line::middle;
			return (true);
	}
}

bool				character::try_go_right(enum line &line)
{
	switch (line)
	{
		case line::left :
			line = line::middle;
			return (true);

		case line::middle :
			line = line::right;
			return (true);

		case line::right :
			return (false);
	}
}

void				character::get_hit()
{
	health--;
	instance->color_mix_state(true);
	color_mix_value = 0.f;
	timer.execute();
}