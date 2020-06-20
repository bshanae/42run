#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void				core::process_callbacks()
{
	glfwPollEvents();

	for (auto &callback : callbacks)
		if (event.type_value != interface::event::type::none and
			event.type_value == callback.get().type)
			callback();

	event.type_value = interface::event::type::none;
}

void				core::process_timers()
{
	for (auto &timer : instance()->timers)
		timer.get().update();
}

void				core::process_rendering()
{
	auto			background = settings().background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	global().renderer->render();

	glfwSwapBuffers(window);
}

void				core::process_updating()
{
	auto			&scene = global().scene;

	global().renderer->animate();

	for (auto &object : scene->objects)
		if (object->is_enabled)
			object->update();
}
