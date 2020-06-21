#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void 				core::execute()
{
	auto			&instance = core::instance();
	auto			renderer = global().renderer;

	float			time_before = 0.f;
	float			time_after = 0.f;

	global().revise();

	renderer->upload_camera_data();
	renderer->upload_light_data();

	while (not glfwWindowShouldClose(instance->window))
	{
		time_before = time();

		global().scene->process_game_objects();

		instance->process_callbacks();
		instance->process_timers();
		instance->process_rendering();
		instance->process_updating();

		time_after = time();

		instance->last_time_delta = time_after - time_before;
	}
}