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

	glfwGetFramebufferSize(window, &settings().window_size.x, &settings().window_size.y);
	glViewport(0, 0, settings().window_size.x, settings().window_size.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	default_settings();

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, callback);

	timer_for_rendering = interface::timer(settings().rendering_frequency);
	timer_for_updating = interface::timer(settings().updating_frequency);

//					Manually connect timers
	timers.push_back(timer_for_rendering);
	timers.push_back(timer_for_updating);
}

					core::~core()
{
	glfwTerminate();
}