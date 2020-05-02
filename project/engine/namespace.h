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
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "common/common.h"
#include "debug.h"

namespace				engine
{
	using				std::vector;
	using				std::list;
	using				std::optional;
	using				std::string;
	using				std::cout;
	using				std::endl;
	using				std::move;
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

	enum class			key
	{
		letter_a = GLFW_KEY_A,
		letter_b = GLFW_KEY_B,
		letter_c = GLFW_KEY_C,
		letter_d = GLFW_KEY_D,
		letter_e = GLFW_KEY_E,
		letter_f = GLFW_KEY_F,
		letter_g = GLFW_KEY_G,
		letter_h = GLFW_KEY_H,
		letter_i = GLFW_KEY_I,
		letter_j = GLFW_KEY_J,
		letter_k = GLFW_KEY_K,
		letter_l = GLFW_KEY_L,
		letter_m = GLFW_KEY_M,
		letter_n = GLFW_KEY_N,
		letter_o = GLFW_KEY_O,
		letter_p = GLFW_KEY_P,
		letter_q = GLFW_KEY_Q,
		letter_r = GLFW_KEY_R,
		letter_s = GLFW_KEY_S,
		letter_t = GLFW_KEY_T,
		letter_u = GLFW_KEY_U,
		letter_v = GLFW_KEY_V,
		letter_w = GLFW_KEY_W,
		letter_x = GLFW_KEY_X,
		letter_y = GLFW_KEY_Y,
		letter_z = GLFW_KEY_Z,
		number_1 = GLFW_KEY_1,
		number_2 = GLFW_KEY_2,
		number_3 = GLFW_KEY_3,
		number_4 = GLFW_KEY_4,
		number_5 = GLFW_KEY_5,
		number_6 = GLFW_KEY_6,
		number_7 = GLFW_KEY_7,
		number_8 = GLFW_KEY_8,
		number_9 = GLFW_KEY_9,
		number_0 = GLFW_KEY_0,
		escape = GLFW_KEY_ESCAPE,
		enter = GLFW_KEY_ENTER,
		left = GLFW_KEY_LEFT,
		up = GLFW_KEY_UP,
		right = GLFW_KEY_RIGHT,
		down = GLFW_KEY_DOWN
	};

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

	class 				texture;

	class				mesh;
	class				model;

	class 				camera;
	class 				renderer;

}