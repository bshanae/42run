#pragma once

#include "engine/namespace.h"

#include "engine/abstract/object_wrap.h"

class				engine::program::shader : public engine::abstract::object_wrap
{
	friend class	engine::program::program;

	enum class		type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};

					shader(type type, const path &source);
					~shader() override;
};
