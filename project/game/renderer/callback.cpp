#include "renderer.h"

using namespace		game;

void				renderer::callback()
{
	auto			key = engine::core::receive_event().read_key();

	static bool		wireframe_mod = false;

	switch (key)
	{
//		case engine::interface::key::letter_a :
//			camera.move(scene::camera::movement::left);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::letter_d :
//			camera.move(scene::camera::movement::right);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::letter_w :
//			camera.move(scene::camera::movement::forth);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::letter_s :
//			camera.move(scene::camera::movement::back);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::letter_q :
//			camera.move(scene::camera::movement::up);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::letter_e :
//			camera.move(scene::camera::movement::down);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::left :
//			camera.rotate(scene::camera::rotation::left);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::right :
//			camera.rotate(scene::camera::rotation::right);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::up :
//			camera.rotate(scene::camera::rotation::up);
//			upload_camera_data();
//			break ;
//
//		case engine::interface::key::down :
//			camera.rotate(scene::camera::rotation::down);
//			upload_camera_data();
//			break ;

		case engine::interface::key::enter :
			wireframe_mod = not wireframe_mod;
			if (wireframe_mod)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break ;

		default :
			return ;
	}
}