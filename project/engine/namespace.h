#pragma once

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "common/common.h"
#include "debug.h"

namespace				engine
{
	using				std::vector;
	using				std::optional;
	using				std::string;
	using				std::cout;
	using				std::endl;
	using				std::filesystem::path;

	using				glm::ivec2;
	using				glm::vec2;
	using				glm::vec3;
	using				glm::vec4;
	using				glm::mat4;

	using				common::exception;

	class				function;
	class				timer;
	class				event;
	class				callback;

	class 				core;

	class 				object_wrap
	{
	protected :
						object_wrap() = default;
	public :

		virtual			~object_wrap() = default;

		virtual void	use(bool state) const
		{
			throw (exception::make_object<exception::id::unimplemented_virtual_method>());
		}

	protected :

		GLuint			object = 0;
	};

	template 			<typename type>
	class				uniform;
	class				shader;
	class				program;

	class				mesh;

	class 				camera;
	class 				renderer;

}