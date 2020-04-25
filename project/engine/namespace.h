#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include "external/glm/glm.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "external/glm/gtc/type_ptr.hpp"
#include "external/glm/gtx/euler_angles.hpp"

#include "common/common.h"

namespace			engine
{
	using			std::string;

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
}