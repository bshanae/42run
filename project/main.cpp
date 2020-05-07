#include "engine/engine.h"

engine::path				giant_path = "/Users/belchenkovova/Desktop/giant/Stone.obj";
engine::path				cobra_path = "/Users/belchenkovova/Desktop/AC Cobra/Shelby.obj";
engine::path				cube_path = "/Users/belchenkovova/Desktop/cube/cube.obj";

int							main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.1f, 0.1f, 0.1f);
	engine::core::use_multisampling = false;
	engine::core::number_of_samples = 0;
	engine::core::use_blending = false;
	engine::core::use_depth_test = true;

	engine::scene::camera::initial_position = engine::vec3(0.f, 5.f, 15.f);
	engine::scene::camera::movement_speed = .7f;
	engine::scene::camera::rotation_speed = 2.f;
	engine::scene::camera::near_plane = 0.1f;
	engine::scene::camera::far_plane = 100.f;

	engine::core::initialize();
	engine::renderer::initialize();
	engine::model::loader::initialize();

	auto					giant = engine::model::loader::load(giant_path);

	engine::renderer::add_target(giant);

	engine::core::execute();

	return (0);
}
