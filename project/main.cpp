#include "engine/engine.h"

struct
{
	engine::path					cube = "/Users/belchenkovova/Desktop/cube/cube.obj";
	engine::path					scene = "/Users/belchenkovova/Desktop/No macs/Scene.obj";
}									paths;

struct
{
	engine::model::model::ptr		cube;
	engine::model::model::ptr		scene;
}									models;

struct
{
	engine::model::instance::ptr	cube;
	engine::model::instance::ptr	scene_left_block;
	engine::model::instance::ptr	scene_right_block;
}									instances;

int									main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.7f, 0.7f, 0.7f);
	engine::core::number_of_samples = 1;

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

	models.scene->analyze();
	models.scene->center();

	instances.cube = engine::model::manager::make_instance(models.cube);
	instances.cube->scale(10.f);
	instances.cube->translate(engine::vec3(300, 100, 0));

	instances.scene_left_block = engine::model::manager::make_instance(models.scene);
	instances.scene_right_block = engine::model::manager::make_instance(models.scene);

	auto							shift = models.scene->read_size() / engine::vec3(2);

	shift.y = 0;
	shift.z = 0;

	instances.scene_left_block->translate(shift * engine::vec3(-1.f));
	instances.scene_right_block->translate(shift * engine::vec3(+1.f));
	instances.scene_right_block->rotate(engine::vec3(0, 180, 0));

//	engine::renderer::add_target(instances.cube);
	engine::renderer::add_target(instances.scene_left_block);
	engine::renderer::add_target(instances.scene_right_block);

	engine::core::execute();

	return (0);
}
