#include "core.h"

#include "engine/game_object/game_object.h"

using namespace		engine;

void				core::process_callbacks()
{
	glfwPollEvents();

	for (auto &callback : callbacks)
		if (event.type_value == interface::event::type::none)
			;
		else if (event.type_value == callback.get().type)
			callback();

	event.type_value = interface::event::type::none;
}

void				core::process_timers()
{
	for (auto &timer : instance()->timers)
		timer.get().update();
}

void				core::process_preparing()
{
	if (not scene)
		return ;

	scene->prepare();

	auto			fill_renderer = [this](const shared<game_object::game_object> &object)
	{
		if (object->renderer_code == typeid(null_renderer).hash_code())
			object->renderer_state = game_object::renderer_state::set_but_null;
		else if (auto iterator = registered_renderers.find(object->renderer_code); iterator == registered_renderers.end())
			error::raise(error::id::renderer_not_found);
		else
		{
			object->renderer = iterator->second;
			object->renderer_state = game_object::renderer_state::set;
		}
	};

	for (auto &object : game_object::game_object::list)
		if (not object->renderer)
			fill_renderer(object);
}

void				core::process_rendering()
{
	if (not scene)
		return ;

	auto			background = settings().background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto &object : scene->objects)
		if (object->state == game_object::state::working)
			object->render();

	glfwSwapBuffers(window);
}

void				core::process_animating()
{
	if (not scene)
		return ;

	for (const auto &object : scene->objects)
		for (const auto &animation_target : object->animation_targets)
			animation_target->skeleton->update();
}

void				core::process_updating()
{
	if (not scene)
		return ;

	for (auto &object : game_object::game_object::list)
		if (object->state == game_object::state::working)
			object->update();
}
