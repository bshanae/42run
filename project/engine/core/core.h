#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/interface/event.h"
#include "engine/interface/callback.h"

class								engine::core
{
public :

	inline static ivec2				window_size;
	inline static string			window_name;
	inline static vec3				background = vec3(0.f, 0.f, 0.f);
	inline static bool				use_blending = false;
	inline static bool				use_multisampling = false;
	inline static int				number_of_samples = 0;
	inline static bool				use_depth_test = false;

private :
									core();
public :
									~core();
private :

	GLFWwindow						*window = nullptr;
	shared_ptr<renderer>			renderer;

	interface::event				event;
	list<interface::callback>		callbacks;

	static void 					callback(GLFWwindow *window, int key, int code, int action, int mode);

IMPLEMENT_GLOBAL_INSTANCER(core)

public :

IMPLEMENT_GLOBAL_INITIALIZER(core)

	static void						execute();

	static void						connect_renderer();

	template					<typename ...args_type>
	static void						generate_callback(args_type ...args)
	{
		instance()->callbacks.emplace_back(args...);
	}

	static const interface::event	&receive_event()
	{
		return (core::instance()->event);
	}
};


