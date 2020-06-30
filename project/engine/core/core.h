#pragma once

#include "engine/namespace.h"

#include "engine/interface/event.h"
#include "engine/interface/callback.h"
#include "engine/interface/timer.h"
#include "engine/scene/scene.h"
#include "engine/renderer/renderer.h"

class								engine::core : public global<engine::core>
{
public :
									core();
									~core();
private :

	GLFWwindow						*window = nullptr;

	map<size_t, shared<renderer>>	registered_renderers;

	shared<scene::scene>			scene;

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

public :

	static void						execute();

	template						<typename renderer_type>
	static void						register_renderer()
	{
		instance()->registered_renderers[typeid(renderer_type).hash_code()] = make_shared<renderer_type>();
	}

	static void						use(const shared<scene::scene> &scene)
	{
		instance()->scene = scene;
	}

	static inline float				time()
	{
		return (glfwGetTime());
	}

	static inline float				time_delta(bool normalize = false)
	{
		return (instance()->last_time_delta / (normalize ? time_delta_normal : 1.f));
	}

	static void						use(interface::callback &callback)
	{
		instance()->callbacks.push_back(callback);
	}

	static void						use(interface::timer &timer)
	{
		instance()->timers.push_back(timer);
	}

	static const interface::event	&receive_event()
	{
		return (core::instance()->event);
	}

private :

	void							process_callbacks();
	void							process_timers();
	void							process_preparing();
	void							process_rendering();
	void							process_animating();
	void							process_updating();
};


