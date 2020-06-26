#include "renderer.h"

using namespace		game;

					renderer::renderer(const shared<scene::scene> &scene) :
						scene(scene),
						engine::renderer(sources().program_vertex, sources().program_fragment)
{
	initialize_uniforms();
	upload_camera_uniforms();
	upload_light_uniforms();
}