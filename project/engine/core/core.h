#pragma once

#include "engine/namespace.h"

#include "engine/interface/event.h"
#include "engine/interface/callback.h"
#include "engine/interface/timer.h"
#include "engine/scene/scene.h"
#include "engine/renderer/renderer.h"

class								engine::core final : public global<engine::core>
{
public :
									core();
									~core() override;
private :

	GLFWwindow						*window = nullptr;

	map<size_t, shared<renderer>>	registered_renderers;

	shared<scene::scene>			scene;

	interface::event				event;

	using 							callbacks_type = list<reference_wrapper<interface::callback>>;
	using 							timers_type = list<reference_wrapper<interface::timer>>;

	callbacks_type					callbacks;
	timers_type						timers;

	constexpr static float			time_delta_normal = 0.03f;
	float							last_time_delta = 0.f;

	static void 					callback(GLFWwindow *window, int key, int code, int action, int mode);

public :

	static void						execute();

	template						<typename renderer_type>
	static void						register_renderer()
	{
		instance()->registered_renderers[typeid(renderer_type).hash_code()] = make_shared<renderer_type>();
	}

	static float					time();
	static float					time_delta(bool normalize = false);

	static void						use(const shared<scene::scene> &scene);
	static void						use(interface::callback &callback);
	static void						use(interface::timer &timer);

	static const interface::event	&receive_event()
	{
		return (core::instance()->event);
	}

	static void						show_polygon_back(bool state);
	static void						use_depth_test(bool state);
	static void						fill_polygon(bool state);

	static void						default_settings();

	static void						window_title(const string &value)
	{
		glfwSetWindowTitle(instance()->window, value.c_str());
	}

private :

	struct							default_settings_values
	{
		static constexpr bool		show_polygon_back = true;
		static constexpr bool		use_depth_test = true;
		static constexpr bool		fill_polygons = true;
	};

	void							process_callbacks();
	void							process_timers();
	void							process_preparing();
	void							process_rendering();
	void							process_animating();
	void							process_updating();
};


