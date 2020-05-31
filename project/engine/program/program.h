#pragma once

#include "engine/namespace.h"
#include "engine/abstract/object_wrap.h"
#include "engine/program/uniform.h"

class					engine::program::program : public engine::abstract::object_wrap
{
private :
						program(const path &vertex_source, const path &fragment_source);
public :
						~program() override;

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(program)

	void				use(bool state) const override
	{
		glUseProgram(state ? object : 0);
	}

	template			<typename type>
	[[nodiscard]] auto	make_uniform(const string &name)
	{
		return (uniform<type>(glGetUniformLocation(object, name.c_str())));
	}
};
