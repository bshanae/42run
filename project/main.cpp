#include "engine/engine.h"
#include "game/game.h"

int									main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.7f, 0.7f, 0.7f);
	engine::core::number_of_samples = 2;

	engine::scene::camera::initial_position = engine::vec3(0.f, 10.f, 100.f);
	engine::scene::camera::movement_speed = 2.f;
	engine::scene::camera::rotation_speed = 2.f;
	engine::scene::camera::near_plane = 10.f;
	engine::scene::camera::far_plane = 1000.f;

	game::room::path = "/Users/belchenkovova/Desktop/42run Workspace/Models/Scene.obj";
	game::character::path = "/Users/belchenkovova/Desktop/42run Workspace/Models/Character.fbx";

	engine::core::initialize();
	engine::renderer::initialize();
	engine::model::manager::initialize();
	game::manager::initialize();

	engine::core::execute();

	return (0);
}
