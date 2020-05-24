#include "engine/engine.h"

struct
{
	engine::path					cube = "/Users/belchenkovova/Desktop/cube/cube.obj";
	engine::path					scene = "/Users/belchenkovova/Desktop/Complete/Scene.obj";
}									paths;

struct
{
	engine::model::model::ptr		cube;
	engine::model::model::ptr		scene;
}									models;

struct
{
	engine::model::instance::ptr	cube;
	engine::model::instance::ptr	scene;
}									instances;

int									main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.7f, 0.7f, 0.7f);
	engine::core::number_of_samples = 4;

	engine::scene::camera::initial_position = engine::vec3(0.f, 10.f, 100.f);
	engine::scene::camera::movement_speed = 2.f;
	engine::scene::camera::rotation_speed = 2.f;
	engine::scene::camera::near_plane = 10.f;
	engine::scene::camera::far_plane = 1000.f;

	engine::core::initialize();
	engine::renderer::initialize();
	engine::model::manager::initialize();

	models.cube = engine::model::manager::make_model(paths.cube);
	models.scene = engine::model::manager::make_model(paths.scene);

	instances.cube = engine::model::manager::make_instance(models.cube);
	instances.cube->scale(10.f);
	instances.cube->translate(engine::vec3(300, 100, 0));

	instances.scene = engine::model::manager::make_instance(models.scene);

//	engine::renderer::add_target(instances.cube);
	engine::renderer::add_target(instances.scene);

	engine::core::execute();

	return (0);
}
