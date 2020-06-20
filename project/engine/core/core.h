#pragma once

#include "engine/namespace.h"

#include "engine/interface/event.h"
#include "engine/interface/callback.h"
#include "engine/interface/timer.h"

class								engine::core
{
private :
									core();
public :
									~core();
private :

	GLFWwindow						*window = nullptr;

	using 							callbacks_type = list<reference_wrapper<interface::callback>>;
	using 							timers_type = list<reference_wrapper<interface::timer>>;

	interface::event				event;
	callbacks_type					callbacks;
	timers_type						timers;

	constexpr static float			time_delta_normal = 0.03f;
	float							last_time_delta = 0.f;

	static void 					callback(GLFWwindow *window, int key, int code, int action, int mode);

	interface::timer				timer_for_rendering;
	interface::timer				timer_for_updating;

IMPLEMENT_GLOBAL_INSTANCER(core)

public :

START_GLOBAL_CUSTOM_INITIALIZER(core)
	instance(false) = shared_ptr<core>(new core());
	connect_with_global();
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void						connect_with_global();

	static inline float				time()
	{
		return (glfwGetTime());
	}

	static inline float				time_delta(bool normalize = false)
	{
		return (instance()->last_time_delta / (normalize ? time_delta_normal : 1.f));
	}

	static void						use_callback(interface::callback &callback)
	{
		instance()->callbacks.push_back(callback);
	}

	static void						use_timer(interface::timer &timer)
	{
		instance()->timers.push_back(timer);
	}

	static const interface::event	&receive_event()
	{
		return (core::instance()->event);
	}

	static void						execute();

private :

	void							process_callbacks();
	void							process_timers();
	void							process_rendering();
	void							process_updating();
};


