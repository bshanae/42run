#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void 				core::execute()
{
	auto			instance = core::instance();

	float			time_before = 0.f;
	float			time_after = 0.f;

	while (not glfwWindowShouldClose(instance->window))
	{
		time_before = time();

		instance->process_callbacks();
		instance->process_timers();
		instance->process_preparing();
		instance->process_rendering();
		instance->process_animating();
		instance->process_updating();

		time_after = time();

		instance->last_time_delta = time_after - time_before;
	}
}