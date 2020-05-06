#pragma once

#include "engine/namespace.h"

#include "engine/object_wrap/object_wrap.h"

class				engine::model::texture : public engine::object_wrap
{
	friend class	engine::renderer;

public :

	explicit		texture(const path &source);
					~texture();

	const path		source;
};


