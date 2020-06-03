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
	glfwWindowHint(GLFW_SAMPLES, settings().number_of_samples);

	window = glfwCreateWindow(
		settings().window_size.x, settings().window_size.y,
		settings().window_name.c_str(),
		nullptr, nullptr);
	if (window == nullptr)
		error::raise(error::id::GLFW_error);
	glfwMakeContextCurrent(window);

	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		error::raise(error::id::GLAD_error);

	glfwGetFramebufferSize(window, &settings().window_size.x, &settings().window_size.y);
	glViewport(0, 0, settings().window_size.x, settings().window_size.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, callback);
}

					core::~core()
{
	glfwTerminate();
}