#pragma once

#include "engine/namespace.h"

class							engine::core
{
public :

	inline static ivec2			window_size;
	inline static string		window_name;
	inline static bool			use_blending = false;
	inline static bool			use_multisampling = false;
	inline static int			number_of_samples = 0;
	inline static bool			use_depth_test = false;

private :
								core();
public :
								~core();
private :

	static core					&instance()
	{
		static core	core;

		return (core);
	}

	GLFWwindow					*window = nullptr;

public :

	static void					start();
	static void					finish()
	{
		auto					&instance = core::instance();

		glfwSetWindowShouldClose(instance.window, GLFW_TRUE);
	}
};


