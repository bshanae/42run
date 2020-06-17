#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_object.h"

class				engine::model::texture : public engine::abstract::OpenGL_object
{
	friend class	engine::renderer;

public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(texture)

	explicit		texture(const path &source);
					~texture() override;
};


