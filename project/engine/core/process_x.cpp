#include "core.h"

#include "engine/renderer/renderer.h"
#include "engine/scene/scene.h"

using namespace		engine;

void				core::process_callbacks()
{
	auto			&instance = core::instance();

	glfwPollEvents();

	for (auto &callback : instance->callbacks)
		if (instance->event.type_value != interface::event::type::none and
			instance->event.type_value == callback.get().type)
			callback();

	instance->event.type_value = interface::event::type::none;
}

void				core::process_timers()
{
	for (auto &timer : instance()->timers)
		timer.get().update();
}

void				core::process_rendering()
{
	auto			&instance = core::instance();
	auto			background = settings().background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	global().renderer->render();

	glfwSwapBuffers(instance->window);
}

void				core::process_updating()
{
	auto			&instance = core::instance();
	auto			&scene = global().scene;

	global().renderer->animate();

	for (auto &object : scene->objects)
		object->update();
}
