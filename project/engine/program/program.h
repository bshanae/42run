#pragma once

#include "engine/namespace.h"

#include "engine/object_wrap/object_wrap.h"
#include "engine/program/uniform.h"

class				engine::program : public object_wrap
{
public :
					program(const string &vertex_source, const string &fragment_source);
					~program() override;

	void			use(bool state) const override
	{
		glUseProgram(state ? object : 0);
	}
};


