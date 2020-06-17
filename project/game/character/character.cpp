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

	model->animate(engine::model::animation(1, 19, 1));

	engine::scene::scene::target(instance);
}