#pragma once

#include <vector>
#include <array>
#include <list>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <typeinfo>
#include <limits>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/types.h>

#include "common/external/glm.h"
#include "common/common.h"

#include "resources/engine/shared.h"

namespace							engine
{
//	-------------------------------	Aliases

	using							std::vector;
	using							std::list;
	using							std::array;
	using							std::map;
	using							std::optional;
	using							std::nullopt;
	using							std::pair;
	using							std::string;
	using							std::ifstream;
	using							std::stringstream;
	using							std::cerr;
	using							std::cout;
	using							std::endl;

	using							std::filesystem::path;
	using							std::filesystem::exists;

	using							std::reference_wrapper;
	using							std::unique_ptr;
	using							std::shared_ptr;
	using							std::make_unique;
	using							std::make_shared;
	using							std::static_pointer_cast;
	using							std::dynamic_pointer_cast;
	using							std::enable_shared_from_this;

	using							std::move;
	using							std::to_string;
	using							std::initializer_list;
	using							std::remove;
	using							std::find;

	using							std::abs;

	using							glm::ivec2;
	using							glm::vec2;
	using							glm::vec3;
	using							glm::vec4;
	using							glm::mat3;
	using							glm::mat4;
	using							glm::quat;
	using							glm::cos;
	using							glm::radians;
	using							glm::lerp;

	template						<typename type>
	using							shared = std::shared_ptr<type>;
	template						<typename type>
	using							unique = std::unique_ptr<type>;

	using							common::float_range;
	using							common::vec3_range;

	using							common::random;

	template						<typename type>
	using							tag = common::tag<type>;

	namespace						error = common::error;
	namespace						warning = common::warning;

//	-------------------------------	Globals

	struct							settings
	{
		ivec2						window_size;
		string						window_name;
		vec3						background = vec3(0.f, 0.f, 0.f);
		int							number_of_samples = 0;

		float						rendering_frequency = 1.f;
		float						updating_frequency = 1.f;

		string						shader_version;
		path						path_to_shared_header;

		float						camera_movement_speed = 0.f;
		float						camera_rotation_speed = 0.f;
		vec3						camera_position = vec3(0.f, 0.f, 0.f);
		float						camera_yaw = -90.f;
		float						camera_pitch = 0.f;
		float						camera_near_plane = 0.1f;
		float						camera_far_plane = 100.f;
	};

	struct settings					&settings();

//	-------------------------------	Local classes

	namespace						converter
	{}

	class 							core;

	namespace						interface
	{
		class						function;
		class						timer;
		class						event;
		class						callback;
		enum class					key;
	}

	namespace						abstract
	{
		template					<typename enum_type, typename underlying_type>
		class						bitflag_wrapper;
		class						OpenGL_wrapper;
	}

	namespace						program
	{
		template					<typename type>
		class						uniform;
		class 						shader;
		class 						program;
	}

	namespace						model
	{
		class						bone;
		class						skeleton;
		class						animation;
		class						texture;
		class						material;
		class						mesh;
		class						loader;
		class						model;
		class						instance;
		class						group;
		class						reader;
	}

	namespace						game_object
	{
		enum						state
		{
			waiting,
			working,
			paused,
			stopped
		};

		class						game_object;
		class						reader;
	}

	namespace						scene
	{
		class						scene;
		class						camera;
		class						light;
		class						reader;
	}

	class 							renderer;
}