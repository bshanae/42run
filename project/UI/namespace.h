#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "engine/engine.h"

namespace							UI
{
	using							std::map;
	using							std::string;
	using							std::filesystem::path;

	using							std::make_unique;
	using							std::make_shared;

	using 							glm::ivec2;
	using							glm::vec3;

	template						<typename type>
	using							shared = std::shared_ptr<type>;
	template						<typename type>
	using							const_shared = std::shared_ptr<const type>;

	template						<typename type>
	using							unique = std::unique_ptr<type>;

	namespace						error = common::error;
	namespace						warning = common::warning;

	class							renderer;

	namespace						font
	{
		class						FreeType_controller;
		class						font;
		class 						symbol;
	}

	class							label;

	struct							global
	{
		shared<UI::renderer>		renderer_for_UI;
		shared<engine::renderer>	renderer_for_engine;
	};

	struct global					&global();
}