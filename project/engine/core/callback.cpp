#include "core.h"

using namespace		engine;

void 				core::callback(GLFWwindow *window, int key, int code, int action, int mode)
{
	auto			*core = (engine::core *)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(core->window, GLFW_TRUE);
	switch (action)
	{
		case GLFW_PRESS :
			core->event.type_value = event::type::key_press;
			break ;

		case GLFW_RELEASE :
			core->event.type_value = event::type::key_release;
			break ;

		case GLFW_REPEAT :
			core->event.type_value = event::type::key_hold;
			break ;

		default :
			return;
	}
	core->event.key_value = static_cast<enum key>(key);
}