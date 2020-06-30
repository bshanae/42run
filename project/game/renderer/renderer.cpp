#include "renderer.h"

using namespace		game;

					renderer::renderer() :
						engine::renderer(sources().vertex_shader, sources().fragment_shader)
{
	initialize_uniforms();
	upload_camera_uniforms();
	upload_light_uniforms();

	auto			scene_checker = [&]()
	{
		check_scene_timer.execute();

		auto		scene = global_scene;

		if (scene::reader::lights_have_changed(scene))
		{
			scene::reader::reset_changes(scene);
			upload_light_uniforms();
		}
	};

	check_scene_timer = interface::timer(scene_check_frequency, scene_checker);

	engine::core::use(check_scene_timer);

	press_callback = interface::callback(interface::event::type::key_press, &renderer::callback, this);
	hold_callback = interface::callback(interface::event::type::key_hold, &renderer::callback, this);

	engine::core::use(press_callback);
	engine::core::use(hold_callback);
}