#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void 				calculate_fps()
{
	static int		number_of_frames = 0;

	static int 		fps_sum = 0;
	static double	fps_count = 0;

	static double	last = 0;
	static double	now = 0;

	now = glfwGetTime();
	number_of_frames++;

	if (now - last >= 1.)
	{
		auto		fps = (int)(number_of_frames / (now - last));
		auto		average_fps = 0.f;

		fps_sum += fps;
		fps_count++;

		average_fps = (float)fps_sum / fps_count;

		std::cout << "\33[2K\r" << "FPS : " << fps << ", Average : " << average_fps << std::flush;
		number_of_frames = 0;
		last = now;
	}
}

void 				core::execute()
{
	auto			&instance = core::instance();

	if (not instance->renderer)
		common::error::raise(common::error::id::core_renderer_not_connected);

	while (not glfwWindowShouldClose(instance->window))
	{
		glfwPollEvents();

		for (auto &callback : instance->callbacks)
			if (instance->event.type_value == callback.type)
				callback();
		instance->event.type_value = interface::event::type::none;

		if (instance->renderer->request)
		{
//			calculate_fps();

			glClearColor(background.x, background.y, background.z, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);

			instance->renderer->render();

			glfwSwapBuffers(instance->window);
		}
	}
}