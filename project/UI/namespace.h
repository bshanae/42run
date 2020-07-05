#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "engine/engine.h"

namespace							UI
{
//	-------------------------------	Aliases

	using							std::cerr;
	using							std::cout;
	using							std::endl;

	using							std::map;
	using							std::vector;
	using							std::string;
	using							std::filesystem::path;
	using							std::max;

	using							std::make_unique;
	using							std::make_shared;
	using							std::dynamic_pointer_cast;

	using 							glm::ivec2;
	using							glm::vec3;
	using							glm::vec2;
	using							glm::mat4;

	template						<typename type>
	using							shared = std::shared_ptr<type>;
	template						<typename type>
	using							unique = std::unique_ptr<type>;

	namespace						error = common::error;
	namespace						warning = common::warning;

	template						<typename type>
	using							tag = common::tag<type>;
	template						<typename type>
	using							global = common::global<type>;

	namespace						converter = engine::converter;
	namespace						game_object = engine::game_object;
	namespace						model = engine::model;
	namespace						program = engine::program;

//	-------------------------------	Globals

	struct							sources
	{
		path						rectangle_vertex_shader;
		path						rectangle_fragment_shader;
		path						symbol_vertex_shader;
		path						symbol_fragment_shader;
	};

	struct sources					&sources();

//	------------------------------- Local classes

	class							renderer;

	namespace						rectangle
	{
		class						rectangle;
		class						renderer;
	}

	namespace						font
	{
		class						manager;
		class						font;
		class 						symbol;
		class 						renderer;
		class 						reader;
	}

	namespace						label
	{
		class						label;
		class						renderer;
	}

	namespace						icon
	{
		class						icon;
	}

	namespace						frame
	{
		class						frame;
		class						renderer;
	}
}