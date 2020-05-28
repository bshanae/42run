#include "character.h"

using namespace					game;

								character::character()
{
	model::manager::flags_wrap	flags;

	flags = model::manager::flags::triangulate;

	common::warning::ignore = true;
	model = model::manager::make_model(path, flags);
	common::warning::ignore = false;

	instance = engine::model::manager::make_instance(model);

	instance->scale(0.1f);
	instance->translate(engine::vec3(0, -10, 0));
	instance->rotate(engine::vec3(0, 180, 0));

	model->animate(engine::model::animation(1, 19, 1));

	engine::renderer::target(instance);
}