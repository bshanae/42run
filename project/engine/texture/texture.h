#pragma once

#include "engine/namespace.h"

class				engine::texture : public engine::object_wrap
{
	friend class	renderer;

public :
					texture(const path &source);
					~texture() override = default;

	const path		source;
};


