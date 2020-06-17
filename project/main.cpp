#include "engine/engine.h"
#include "game/game.h"

int									main()
{
	common::seed = 123;

	engine::settings().window_size = engine::ivec2(1280, 720);
	engine::settings().window_name = "42run";
	engine::settings().background = engine::vec3(0.7f, 0.7f, 0.7f);
	engine::settings().number_of_samples = 1;

	engine::settings().glsl_version = "330 core";
	engine::settings().glsl_path = "project/resources/engine";

	engine::settings().camera_position = engine::vec3(0.f, 10.f, 100.f);
	engine::settings().camera_movement_speed = 2.f;
	engine::settings().camera_rotation_speed = 2.f;
	engine::settings().camera_near_plane = 10.f;
	engine::settings().camera_far_plane = 1000.f;

	game::sources().room = "/Users/belchenkovova/Desktop/42run Workspace/Models/Room.obj";
	game::sources().chair = "/Users/belchenkovova/Desktop/42run Workspace/Models/Chair.obj";
	game::sources().mac = "/Users/belchenkovova/Desktop/42run Workspace/Models/iMac.obj";
	game::sources().keyboard = "/Users/belchenkovova/Desktop/42run Workspace/Models/Keyboard.obj";
	game::sources().character = "/Users/belchenkovova/Desktop/42run Workspace/Models/Character.fbx";

	engine::core::initialize();
	engine::renderer::initialize();
	engine::scene::scene::initialize();
	engine::model::manager::initialize();
	game::manager::initialize();

	engine::core::execute();

	return (0);
}
