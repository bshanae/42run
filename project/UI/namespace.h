#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "engine/engine.h"

namespace							UI
{
//	-------------------------------	Aliases

	using							std::map;
	using							std::string;
	using							std::filesystem::path;
	using							std::max;

	using							std::make_unique;
	using							std::make_shared;

	using 							glm::ivec2;
	using							glm::vec3;
	using							glm::mat4;

	template						<typename type>
	using							shared = std::shared_ptr<type>;
	template						<typename type>
	using							unique = std::unique_ptr<type>;

	namespace						error = common::error;
	namespace						warning = common::warning;

	template						<typename type>
	using							global = common::global<type>;

	namespace						model = engine::model;

//	-------------------------------	Globals

	struct							sources
	{
		path						vertex_shader;
		path						fragment_shader;
	};

	struct sources					&sources();

//	------------------------------- Local classes

	class							renderer;

	namespace						font
	{
		class						manager;
		class						font;
		class 						symbol;
		class 						reader;
	}

	class							label;
}