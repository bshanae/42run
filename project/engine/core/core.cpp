#include "core.h"

using namespace		engine;

					core::core()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (use_multisampling)
		glfwWindowHint(GLFW_SAMPLES, number_of_samples);

	window = glfwCreateWindow(window_size.x, window_size.y, window_name.c_str(), nullptr, nullptr);
	if (window == nullptr)
		throw (exception::make_object<exception::id::GLFW>());
	glfwMakeContextCurrent(window);

	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw (exception::make_object<exception::id::GLAD>());

	glfwGetFramebufferSize(window, &window_size.x, &window_size.y);
	glViewport(0, 0, window_size.x, window_size.y);

	if (use_blending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (use_multisampling)
		glEnable(GL_MULTISAMPLE);

	if (use_depth_test)
		glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(window, this);
}

					core::~core()
{
	glfwTerminate();
}