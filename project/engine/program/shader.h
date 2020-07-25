#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_wrapper.h"

class				engine::program::shader : public engine::abstract::OpenGL_wrapper
{
	friend class	engine::program::program;

	enum class		type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};
					shader(type type, const string &source);
					~shader() override;
};
