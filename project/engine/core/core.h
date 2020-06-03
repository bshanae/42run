#pragma once

#include "engine/namespace.h"

#include "engine/interface/event.h"
#include "engine/interface/callback.h"

class								engine::core
{
private :
									core();
public :
									~core();
private :

	GLFWwindow						*window = nullptr;

	interface::event				event;
	list<interface::callback>		callbacks;

	static void 					callback(GLFWwindow *window, int key, int code, int action, int mode);

IMPLEMENT_GLOBAL_INSTANCER(core)

public :

START_GLOBAL_CUSTOM_INITIALIZER(core)
	connect_with_global();
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void						execute();

	static void						connect_with_global();

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


