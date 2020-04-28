#pragma once

#include "engine/namespace.h"

#include "engine/renderer/renderer.h"

class							engine::core
{
public :

	inline static ivec2			window_size;
	inline static string		window_name;
	inline static vec3			background = vec3(0.f, 0.f, 0.f);
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
	class renderer				*renderer = nullptr;

public :

	static void 				initialize()
	{
		auto					&instance = core::instance();
	}

	static void					start();
	static void					finish()
	{
		auto					&instance = core::instance();

		glfwSetWindowShouldClose(instance.window, GLFW_TRUE);
	}

	static void					attach_renderer(class renderer &renderer)
	{
		auto					&instance = core::instance();

		instance.renderer = &renderer;
	}
};


