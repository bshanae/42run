#include "core.h"

using namespace		engine;

void 				core::start()
{
	auto			&instance = core::instance();

	while (not glfwWindowShouldClose(instance.window))
		glfwPollEvents();
}