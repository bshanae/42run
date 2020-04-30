#pragma once

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

#include "external/glad/include/glad/glad.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include "external/glm/glm.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "external/glm/gtc/type_ptr.hpp"
#include "external/glm/gtx/euler_angles.hpp"

#include "common/common.h"
#include "debug.h"

namespace			engine
{
	using			std::string;
	using			std::cout;
	using			std::endl;

	using			glm::ivec2;
	using			glm::vec3;
	using			glm::vec4;
	using			glm::mat4;

	using			common::exception;

	class			function;
	class			timer;
	class			event;
	class			callback;

	class 			core;

	class			object_wrap;

	template 		<typename type>
	class			uniform;
	class			shader;
	class			program;

	enum class		memory_management : GLuint
	{
		static_draw = GL_STATIC_DRAW,
		dynamic_draw = GL_DYNAMIC_DRAW,
		stream_draw = GL_STREAM_DRAW
	};

	template		<typename type = float,
					int group = 3,
					engine::memory_management management = engine::memory_management::static_draw>
	class			vbo;
	class			eab;
	class			vao;
	template		<engine::memory_management management = engine::memory_management::static_draw>
	class			model;

	class			mesh;

	class 			camera;
	class 			renderer;

}