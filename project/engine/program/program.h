#pragma once

#include "engine/namespace.h"

#include "engine/program/uniform.h"

class				engine::program : public object_wrap
{
public :
					program(const path &vertex_source, const path &fragment_source);
					~program() override;

	void			use(bool state) const override
	{
		glUseProgram(state ? object : 0);
	}

	[[nodiscard]]
	GLuint			find_uniform_location(const string &name)
	{
		return (glGetUniformLocation(object, name.c_str()));
	}
};


