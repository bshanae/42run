#pragma once

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <initializer_list>
#include <type_traits>

#include "common/external/glad.h"
#include "common/external/glfw.h"
#include "common/external/assimp.h"
#include "common/external/glm.h"
#include "common/common.h"

#include "resources/engine/shared.h"

namespace				engine
{
	using				std::vector;
	using				std::list;
	using				std::optional;
	using				std::pair;
	using				std::string;
	using				std::ifstream;
	using				std::stringstream;

	using				std::filesystem::path;
	using				std::filesystem::exists;

	using				std::unique_ptr;
	using				std::shared_ptr;
	using				std::make_unique;
	using				std::make_shared;

	using				std::move;
	using				std::to_string;
	using				std::initializer_list;

	using				glm::ivec2;
	using				glm::vec2;
	using				glm::vec3;
	using				glm::vec4;
	using				glm::mat3;
	using				glm::mat4;
	using				glm::quat;

	using				common::float_range;
	using				common::vec3_range;

	using				common::random;

	struct				settings
	{
		ivec2			window_size;
		string			window_name;
		vec3			background = vec3(0.f, 0.f, 0.f);
		int				number_of_samples = 0;

		string			glsl_version;
		path			glsl_path;

		float			camera_movement_speed = 0.f;
		float			camera_rotation_speed = 0.f;
		vec3			camera_position = vec3(0.f, 0.f, 0.f);
		float			camera_yaw = -90.f;
		float			camera_pitch = 0.f;
		float			camera_near_plane = 0.1f;
		float			camera_far_plane = 100.f;
	};

	struct settings		&settings();

	namespace			converter
	{}

	class 				core;

	namespace			interface
	{
		class			function;
		class			timer;
		class			event;
		class			callback;
		enum class		key;
	}

	namespace			abstract
	{
		template		<typename enum_type, typename underlying_type>
		class			enum_wrap;
		class			object_wrap;
	}

	namespace			program
	{
		template		<typename type>
		class			uniform;
		class 			shader;
		class 			program;
	}

	namespace			model
	{
		class			bone;
		class			skeleton;
		class			animation;
		class			texture;
		class			material;
		class			mesh;
		class			manager;
		class			model;
		class			instance;
		class			group;
	}

	namespace			scene
	{
		class			camera;
		class			light;
		class			scene;
	}

	class 				renderer;
}