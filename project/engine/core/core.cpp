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

	window = glfwCreateWindow
	(
		settings().window_size.x, settings().window_size.y,
		settings().window_name.c_str(),
		nullptr, nullptr
	);

	if (window == nullptr)
		error::raise(error::id::GLFW_error);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		error::raise(error::id::GLEW_error);

	ivec2			new_size;

	glfwGetFramebufferSize(window, &new_size.x, &new_size.y);
	glViewport(0, 0, new_size.x, new_size.y);

	settings().window_scaling = new_size / settings().window_size;
	settings().window_size = new_size;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	default_settings();

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, callback);
}

					core::~core()
{
	glfwTerminate();
}