#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void 				core::execute()
{
	auto			&instance = core::instance();
	auto			renderer = global().renderer;

	global().revise();

	renderer->upload_camera_data();
	renderer->upload_light_data();

	while (not glfwWindowShouldClose(instance->window))
	{
		instance->process_callbacks();
		instance->process_rendering();
		instance->process_updating();
	}
}