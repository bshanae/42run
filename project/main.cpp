#include "engine/engine.h"

engine::path				custom_path = "/Users/belchenkovova/Downloads/Boxing.fbx";
engine::path				caterpillar_path = "/Users/belchenkovova/Desktop/Caterpillar/caterpillar.fbx";
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

	engine::scene::camera::initial_position = engine::vec3(0.f, 80.f, 500.f);
	engine::scene::camera::movement_speed = 100.f;
	engine::scene::camera::rotation_speed = 2.f;
	engine::scene::camera::near_plane = 50.f;
	engine::scene::camera::far_plane = 10000.f;

	engine::core::initialize();
	engine::renderer::initialize();
	engine::model::loader::initialize();

	auto					model = engine::model::loader::load(custom_path);

	engine::renderer::add_target(model);

	model->animate(engine::model::animation(0, 245, 1));

	engine::core::execute();

	return (0);
}
