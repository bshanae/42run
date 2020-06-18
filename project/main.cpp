#include "engine/engine.h"
#include "game/game.h"

int					main()
{
	common::seed = 42;

	engine::settings().window_size = engine::ivec2(1280, 720);
	engine::settings().window_name = "42run";
	engine::settings().background = engine::vec3(0.7f, 0.7f, 0.7f);
	engine::settings().number_of_samples = 1;

	engine::settings().rendering_frequency = 1 / 100.f;
	engine::settings().updating_frequency = 1 / 50.f;

	engine::settings().glsl_version = "330 core";
	engine::settings().glsl_path = "project/resources/engine";

	engine::settings().camera_position = engine::vec3(0.f, 10.f, 100.f);
	engine::settings().camera_movement_speed = 2.f;
	engine::settings().camera_rotation_speed = 2.f;
	engine::settings().camera_near_plane = 10.f;
	engine::settings().camera_far_plane = 350.f;

	game::sources().room = "project/resources/game/models/Room.obj";
	game::sources().chair = "project/resources/game/models/Chair.obj";
	game::sources().mac = "project/resources/game/models/iMac.obj";
	game::sources().keyboard = "project/resources/game/models/Keyboard.obj";
	game::sources().character = "project/resources/game/models/Character.fbx";

	engine::core::initialize();
	engine::renderer::initialize();
	engine::scene::scene::initialize();
	engine::model::manager::initialize();

	game::manager::initialize();

	engine::core::execute();

	return (0);
}
