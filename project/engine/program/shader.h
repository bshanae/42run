#pragma once

#include "engine/namespace.h"

#include "engine/object_wrap/object_wrap.h"

class				engine::shader : public object_wrap
{
	friend class	engine::program;

private :

	enum class		type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};

					shader(type type, const string &source);
					~shader() override;
};


