#include "game/game.h"

int					main()
{
#if DEBUG_VERBOSE
	common::warning::is_critical = true;
#endif

	engine::settings().window_size = engine::ivec2(1280, 720);
	engine::settings().window_name = "";
	engine::settings().number_of_samples = 1;

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
	game::sources().bonus_coin = "project/resources/game/models/Coin.obj";
	game::sources().bonus_heal = "project/resources/game/models/Heal.obj";
	game::sources().bonus_protection = "project/resources/game/models/Protection.obj";

	game::settings().title_scene_background = engine::vec3(0.1f);
	game::settings().game_scene_background = engine::vec3(0.95f);
	game::settings().fog_density = 0.004;
	game::settings().fog_gradient = 8.f;
	game::settings().number_of_faded_rows = 2;
	game::settings().obstacle_generation_wait = 10;
	game::settings().bonus_generation_wait = 20;
	game::settings().hollow_row_spawning_frequency = common::int_range(6, 16);
	game::settings().chair_spawning_frequency = common::int_range(2, 4);
	game::settings().coin_spawning_frequency = common::int_range(4, 10);
	game::settings().heal_spawning_frequency = common::int_range(20,40);
	game::settings().protection_spawning_frequency = common::int_range(80, 100);
	game::settings().initial_room_speed = 1.875f;
	game::settings().initial_character_speed = 0.625f;
	game::settings().increase_of_room_speed = 0.001f;
	game::settings().increase_of_character_speed = 0.001f;
	game::settings().maximum_room_speed_factor = 1.3f;
	game::settings().maximum_character_speed_factor = 1.3f;
	game::settings().hit_start = 0.6f;
	game::settings().hit_end = 0.f;
	game::settings().hit_color = engine::vec3(1.f, 0.f, 0.f);
	game::settings().hit_duration = 1.5f;
	game::settings().coin_value = 500.f;
	game::settings().coin_start = 0.6f;
	game::settings().coin_end = 0.f;
	game::settings().coin_duration = 1.2f;
	game::settings().protection_start = 0.6f;
	game::settings().protection_end = 0.f;
	game::settings().protection_color = engine::vec3(0.11f, 0.65f, 0.58f);
	game::settings().protection_duration = 20.f;

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
