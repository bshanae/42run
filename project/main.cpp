#include "engine/engine.h"


engine::path				cube_path = "/Users/belchenkovova/Desktop/cube/cube.obj";
engine::path				table_path = "/Users/belchenkovova/Desktop/table.obj";
engine::path				imac_path = "/Users/belchenkovova/Desktop/iMac/mpm_f18__Apple_iMac_27.obj";
engine::path				keyboard_path = "/Users/belchenkovova/Desktop/Apple Keyboard/mpm_f17__Apple_Keyboard.obj";
engine::path				floor_path = "/Users/belchenkovova/Desktop/floor/floor.obj";

int							main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.1f, 0.1f, 0.1f);
	engine::core::use_multisampling = true;
	engine::core::number_of_samples = 3;
	engine::core::use_blending = false;
	engine::core::use_depth_test = true;

	engine::scene::camera::initial_position = engine::vec3(0.f, 0.f, 500.f);
	engine::scene::camera::movement_speed = 10.f;
	engine::scene::camera::rotation_speed = 2.f;
	engine::scene::camera::near_plane = 10.f;
	engine::scene::camera::far_plane = 5000.f;

	engine::core::initialize();
	engine::renderer::initialize();
	engine::model::manager::initialize();

#if 1
	auto					floor_model = engine::model::manager::make_model(floor_path);
	auto					floor_instance = engine::model::manager::make_instance(floor_model);

	floor_instance->scale(100.f);
	floor_instance->rotate(engine::vec3(10.f, 0.f, 0.f));
	engine::renderer::add_target(floor_instance);
#else
	auto					imac_model = engine::model::manager::make_model(imac_path);
	auto					table_model = engine::model::manager::make_model(table_path);
	auto					keyboard_model = engine::model::manager::make_model(keyboard_path);
	auto					floor_model = engine::model::manager::make_model(floor_path);

	auto					imac_instance_a = engine::model::manager::make_instance(imac_model);
	auto					imac_instance_b = engine::model::manager::make_instance(imac_model);
	auto					table_instance = engine::model::manager::make_instance(table_model);
	auto					keyboard_instance = engine::model::manager::make_instance(keyboard_model);
	auto					floor_instance = engine::model::manager::make_instance(floor_model);

	imac_instance_a->scale(0.1f);
	imac_instance_a->translate(engine::vec3(-45.f, 64.f, 0.f));

	imac_instance_b->scale(0.1f);
	imac_instance_b->translate(engine::vec3(+45.f, 64.f, 0.f));
	imac_instance_b->rotate(engine::vec3(0.f, 180.f, 0.f));

//	keyboard_instance->rotate(engine::vec3(45.f, 0.f, 0.f));

	floor_instance->rotate(engine::vec3(90.f, 0.f, 0.f));

//	engine::renderer::add_target(table_instance);
//	engine::renderer::add_target(imac_instance_a);
//	engine::renderer::add_target(imac_instance_b);
//	engine::renderer::add_target(keyboard_instance);
	engine::renderer::add_target(floor_instance);
#endif

	engine::core::execute();

	return (0);
}
