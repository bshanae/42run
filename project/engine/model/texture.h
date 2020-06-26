#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_wrapper.h"

class				engine::model::texture : public engine::abstract::OpenGL_wrapper
{
	friend class	engine::model::reader;

public :

	explicit		texture(const path &source);
					~texture() override;
};


