#pragma once

#include "engine/engine.h"

namespace			game
{
	using			engine::path;
	using			engine::vec3;

	namespace		model
	{
		using		engine::model::manager;
		using		engine::model::model;
		using		engine::model::instance;
	}

	class			model_wrap;

	class 			room;
	class 			character;
	class			obstacle;

	class 			manager;
}