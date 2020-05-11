#pragma once

#include "engine/namespace.h"

#include "engine/abstract/pointer.h"
#include "engine/abstract/holder.h"

class				engine::model::texture : public engine::abstract::holder
{
	friend class	engine::renderer;

public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(texture)

	explicit		texture(const path &source);
					~texture();

	const path		source;
};


