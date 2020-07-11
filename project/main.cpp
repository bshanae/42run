#include "game/game.h"

int					main()
{
#if DEBUG
	common::warning::is_critical = false;
#endif

	common::seed = 42;

	engine::settings().window_size = engine::ivec2(1280, 720);
	engine::settings().window_name = "42run";
	engine::settings().background = engine::vec3(1.f);
	engine::settings().number_of_samples = 1;

	engine::settings().rendering_frequency = 1 / 60.f;
	engine::settings().updating_frequency = 1 / 40.f;

	engine::settings().shader_version = "330 core";
	engine::settings().path_to_shared_header = "project/resources/engine";

	engine::settings().camera_position = engine::vec3(0.f, 22.f, 50.f);
	engine::settings().camera_yaw = -90;
	engine::settings().camera_pitch = -12;
	engine::settings().camera_movement_speed = 2.f;
	engine::settings().camera_rotation_speed = 2.f;
	engine::settings().camera_near_plane = 10.f;
	engine::settings().camera_far_plane = 350.f;

	UI::sources().rectangle_vertex_shader = "project/resources/UI/shaders/rectangle.vertex.glsl";
	UI::sources().rectangle_fragment_shader = "project/resources/UI/shaders/rectangle.fragment.glsl";
	UI::sources().symbol_vertex_shader = "project/resources/UI/shaders/symbol.vertex.glsl";
	UI::sources().symbol_fragment_shader = "project/resources/UI/shaders/symbol.fragment.glsl";

	game::sources().vertex_shader = "project/resources/game/shaders/vertex.glsl";
	game::sources().fragment_shader = "project/resources/game/shaders/fragment.glsl";
	game::sources().room = "project/resources/game/models/Room.obj";
	game::sources().chair = "project/resources/game/models/Chair.obj";
	game::sources().mac = "project/resources/game/models/iMac.obj";
	game::sources().keyboard = "project/resources/game/models/Keyboard.obj";
	game::sources().character = "project/resources/game/models/Character.fbx";
	game::sources().circle = "project/resources/UI/icons/circle.png";
	game::sources().font = "project/resources/UI/fonts/HelveticaNeue.ttc";

	game::settings().faster_scene = true;
	game::settings().fog_density = 0.004;
	game::settings().fog_gradient = 8.f;
	game::settings().number_of_faded_rows = 2;
	game::settings().obstacle_generation_wait = 5;
	game::settings().hollow_row_spawning_frequency = common::int_range(8, 15);
	game::settings().chair_spawning_frequency = common::int_range(4, 8);
	game::settings().initial_room_speed = 1.5f;
	game::settings().initial_character_speed = 0.5f;
	game::settings().initial_row_value = 20.f;
	game::settings().increase_of_room_speed = 0.0001f;
	game::settings().increase_of_character_speed = 0.0001f;
	game::settings().increase_of_row_value = 0.05f;
	game::settings().maximum_room_speed_factor = 2.f;
	game::settings().maximum_character_speed_factor = 2.f;
	game::settings().maximum_row_value_factor = 4.f;
	game::settings().hit_effect_duration = 1.5f;
	game::settings().hit_effect_color = engine::vec3(1.f, 0.f, 0.f);
	game::settings().hit_effect_factor = 0.6f;
	game::settings().hit_effect_fade_out_step = 0.04f;

	engine::core::initialize();
	UI::font::manager::initialize();
	game::manager::initialize();

	engine::core::register_renderer<game::renderer>();
	engine::core::register_renderer<UI::font::renderer>();
	engine::core::register_renderer<UI::rectangle::renderer>();
	engine::core::register_renderer<UI::label::renderer>();
	engine::core::register_renderer<UI::frame::renderer>();

	engine::core::execute();

	return (0);
}
