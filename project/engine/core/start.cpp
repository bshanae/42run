#include "core.h"

using namespace		engine;

void 				core::start()
{
	auto			&instance = core::instance();

	while (not glfwWindowShouldClose(instance.window))
	{
		glfwPollEvents();

		glClearColor(background.x, background.y, background.z, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		instance.renderer->render();

		glfwSwapBuffers(instance.window);
	}
}