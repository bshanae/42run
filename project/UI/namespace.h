#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "engine/engine.h"

namespace			UI
{
	using			std::map;
	using			std::filesystem::path;

	using 			glm::ivec2;
	using			glm::vec3;

	namespace		error = common::error;
	namespace		warning = common::warning;

	namespace		font
	{
		class		FreeType_controller;
		class		font;
		class 		symbol;
	}
}