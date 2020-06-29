#include "game/game.h"

int					main()
{
	common::seed = 42;

	engine::settings().window_size = engine::ivec2(720, 480);
	engine::settings().window_name = "42run";
	engine::settings().background = engine::vec3(1.f);
	engine::settings().number_of_samples = 1;

	engine::settings().rendering_frequency = 1 / 60.f;
	engine::settings().updating_frequency = 1 / 40.f;

	engine::settings().glsl_version = "330 core";
	engine::settings().glsl_path = "project/resources/engine";

	engine::settings().camera_position = engine::vec3(0.f, 22.f, 50.f);
	engine::settings().camera_yaw = -90;
	engine::settings().camera_pitch = -12;
	engine::settings().camera_movement_speed = 2.f;
	engine::settings().camera_rotation_speed = 2.f;
	engine::settings().camera_near_plane = 10.f;
	engine::settings().camera_far_plane = 350.f;

	game::sources().program_vertex = "project/resources/engine/main.vertex.glsl";
	game::sources().program_fragment = "project/resources/engine/main.fragment.glsl";
	game::sources().room = "project/resources/game/models/Room.obj";
	game::sources().chair = "project/resources/game/models/Chair.obj";
	game::sources().mac = "project/resources/game/models/iMac.obj";
	game::sources().keyboard = "project/resources/game/models/Keyboard.obj";
	game::sources().character = "project/resources/game/models/Character.fbx";

	game::settings().number_of_faded_rows = 2;
	game::settings().obstacle_generation_wait = 5;
	game::settings().hollow_row_spawning_frequency = common::int_range(8, 20);
	game::settings().chair_spawning_frequency = common::int_range(4, 12);

	engine::core::initialize();
	engine::model::manager::initialize();
	game::manager::initialize();

	engine::core::register_renderer<game::renderer>();
//	engine::core::register_renderer<UI::renderer>();

	engine::core::execute();

	return (0);
}
