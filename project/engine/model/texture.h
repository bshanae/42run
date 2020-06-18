#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_wrapper.h"

class				engine::model::texture : public engine::abstract::OpenGL_wrapper
{
	friend class	engine::renderer;

public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(texture)

	explicit		texture(const path &source);
					~texture() override;
};


