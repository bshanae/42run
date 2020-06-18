#pragma once

#include "engine/engine.h"

namespace				game
{
	using				engine::path;

	using				engine::vec3;
	using				engine::vec4;
	using				engine::float_range;
	using				engine::vec3_range;

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