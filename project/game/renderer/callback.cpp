#include "renderer.h"

using namespace		game;

void				renderer::callback()
{
#if DEBUG_VERBOSE
	auto			key = engine::core::receive_event().read_key();
	auto			camera = scene::reader::camera(global_scene);

	switch (key)
	{
		case engine::interface::key::letter_a :
			camera->move(scene::camera::movement::left);
			break ;

		case engine::interface::key::letter_d :
			camera->move(scene::camera::movement::right);
			break ;

		case engine::interface::key::letter_w :
			camera->move(scene::camera::movement::forth);
			break ;

		case engine::interface::key::letter_s :
			camera->move(scene::camera::movement::back);
			break ;

		case engine::interface::key::letter_q :
			camera->move(scene::camera::movement::up);
			break ;

		case engine::interface::key::letter_e :
			camera->move(scene::camera::movement::down);
			break ;

		case engine::interface::key::left :
			camera->rotate(scene::camera::rotation::left);
			break ;

		case engine::interface::key::right :
			camera->rotate(scene::camera::rotation::right);
			break ;

		case engine::interface::key::up :
			camera->rotate(scene::camera::rotation::up);
			break ;

		case engine::interface::key::down :
			camera->rotate(scene::camera::rotation::down);
			break ;

		default :
			return ;
	}

	upload_camera_uniforms();
#endif
}