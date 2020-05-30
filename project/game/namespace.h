#pragma once

#include "engine/engine.h"

namespace				game
{
	using				engine::path;
	using				engine::vec3;

	struct				sources
	{
		path			room;
		path			chair;
		path			mac;
		path			keyboard;
		path			character;
	};

	struct sources		&sources();

	namespace			model
	{
		using			engine::model::model;
		using			engine::model::instance;
		using			engine::model::group;
		using			engine::model::manager;
		using			flags = engine::model::manager::flags;
		using			flags_wrap = engine::model::manager::flags_wrap;
	}

	class				model_wrap;

	class 				room;
	class 				character;
	class				obstacle;

	class 				manager;
}