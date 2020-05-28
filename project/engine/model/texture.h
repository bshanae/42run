#pragma once

#include "engine/namespace.h"

#include "engine/abstract/object_wrap.h"

class				engine::model::texture : public engine::abstract::object_wrap
{
	friend class	engine::renderer;

public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(texture)

	explicit		texture(const path &source);
					~texture() override;
};


