#pragma once

#include <deque>

#include "engine/engine.h"

namespace							game
{
	using							std::vector;
	using							std::list;
	using							std::deque;
	using							std::reference_wrapper;
	using							std::cerr;
	using							std::cout;
	using							std::endl;
	using							std::to_string;
	using							std::shared_ptr;
	using							std::unique_ptr;
	using							std::make_shared;
	using							std::make_unique;
	using							std::static_pointer_cast;
	using							std::dynamic_pointer_cast;

	using							engine::path;

	using							std::find_if;
	using							std::remove_if;

	template						<typename type>
	using							shared = std::shared_ptr<type>;
	template						<typename type>
	using							unique = std::unique_ptr<type>;

	using							engine::vec3;
	using							engine::vec4;
	using							engine::mat4;

	namespace						error = common::error;
	namespace						warning = common::warning;

	using							common::int_range;
	using							common::float_range;
	using							common::vec3_range;
	using							common::random;

	namespace						converter = engine::converter;
	namespace						game_object = engine::game_object;

	namespace						scene
	{
		using						engine::scene::scene;
		using						engine::scene::light;
		using						engine::scene::camera;
		using						engine::scene::reader;
	};

	namespace						model
	{
		using						engine::model::model;
		using						engine::model::instance;
		using						engine::model::group;
		using						engine::model::manager;
		using						engine::model::animation;
		using						engine::model::skeleton;
		using						engine::model::reader;

		using						flag = engine::model::manager::flag;
		using						flag_wrapper = engine::model::manager::flag_wrapper;
	}

	namespace						interface
	{
		using						engine::interface::event;
		using						engine::interface::callback;
		using						engine::interface::timer;
	}

	struct							constants
	{
		static constexpr float		distance_between_lines = 6.f;
	};

	struct							sources
	{
		path						program_vertex;
		path						program_fragment;
		path						room;
		path						chair;
		path						mac;
		path						keyboard;
		path						character;
	};

	struct sources					&sources();

	struct							settings
	{
		int							number_of_faded_rows;
		int							obstacle_generation_wait;
		int_range					hollow_row_spawning_frequency;
		int_range					chair_spawning_frequency;
	};

	struct settings					&settings();

	enum class 						line : unsigned int
	{
		left = 0x001,
		middle = 0x010,
		right = 0x100
	};

	enum class						state : unsigned int
	{
		running = 0x01,
		jumping = 0x10
	};

	using							line_wrapper = engine::abstract::bitflags_wrapper<line>;
	using							state_wrapper = engine::abstract::bitflags_wrapper<state>;

	class							renderer;

	class 							room;
	class 							character;

	namespace						obstacle
	{
		class						obstacle;
		class						chair;
	}

	class 							manager;

	struct							global
	{
		shared<game::renderer>		renderer_for_game;
		shared<engine::renderer>	renderer_for_engine;
		shared<scene::scene>		scene;
	};

	struct global					&global();
}