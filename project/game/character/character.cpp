#include "character.h"

using namespace					game;

								character::character()
{
	model::manager::flags_wrap	flags;

	flags = model::manager::flags::triangulate;

	common::warning::ignore = true;
	model = model::manager::make_model(sources().character, flags);
	common::warning::ignore = false;

	instance = engine::model::manager::make_instance(model);

	instance->scale(0.095f);
	instance->rotate(engine::vec3(0, 180, 0));

	animations.run = model::animation(1, 19, 1.2, true);
	animations.jump = model::animation(20, 63, 1.2, false);

	model->animate(animations.run);

	game_object::render_target(instance);
	game_object::animation_target(model);

	callback = interface::callback(interface::event::type::key_press, &character::callback_functor, this);

	engine::core::use_callback(callback);
}

void							character::callback_functor()
{
	auto						key = engine::core::receive_event().read_key();

	switch (key)
	{
		case engine::interface::key::space :
			model->animate(animations.jump);
			break;

		default :
			break ;
	}
}