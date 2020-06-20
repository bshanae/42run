#pragma once

#include "engine/engine.h"

namespace				game
{
	using				std::vector;
	using				std::list;
	using				std::reference_wrapper;

	using				engine::path;

	using				std::remove_if;

	using				engine::vec3;
	using				engine::vec4;
	using				engine::float_range;
	using				engine::vec3_range;

	using				engine::game_object;
	namespace			scene
	{
		using			engine::scene::scene;
		using			engine::scene::light;
	};

	namespace			model
	{
		using			engine::model::model;
		using			engine::model::instance;
		using			engine::model::group;
		using			engine::model::manager;
		using			engine::model::animation;
		using			flags = engine::model::manager::flag;
		using			flags_wrapper = engine::model::manager::flags_wrapper;
	}

	namespace			interface
	{
		using			engine::interface::event;
		using			engine::interface::callback;
		using			engine::interface::timer;
	}

	struct				sources
	{
		path			room;
		path			chair;
		path			mac;
		path			keyboard;
		path			character;
	};

	struct sources		&sources();

	struct				settings
	{
	};

	struct settings		&settings();

	enum class 			line : unsigned int
	{
		left = 0x001,
		middle = 0x010,
		right = 0x100
	};

	enum class			state : unsigned int
	{
		running = 0x01,
		jumping = 0x10
	};

	using				line_wrapper = engine::abstract::bitflags_wrapper<line>;
	using				state_wrapper = engine::abstract::bitflags_wrapper<state>;

	class 				room;
	class 				character;

	namespace			obstacle
	{
		class			obstacle;
		class			chair;
		class			column;
	}

	class 				manager;
}