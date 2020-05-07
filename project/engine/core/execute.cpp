#include "core.h"

using namespace		engine;

void 				core::execute()
{
	auto			&instance = core::instance();

	while (not glfwWindowShouldClose(instance->window))
	{
		glfwPollEvents();

		for (auto &callback : instance->callbacks)
			if (instance->event.type_value == callback.type)
				callback();
		instance->event.type_value = interface::event::type::none;

//		if (instance.renderer->request)
//		{
//			glClearColor(background.x, background.y, background.z, 1.f);
//			glClear(GL_COLOR_BUFFER_BIT);
//			glClear(GL_DEPTH_BUFFER_BIT);
//
//			instance.renderer->render();
//
//			glfwSwapBuffers(instance.window);
//		}
	}
}