#pragma once

#include "engine/namespace.h"

class				engine::texture : public engine::object_wrap
{
	friend class	renderer;

public :

	explicit 		texture(const path &source);
					~texture() override;

	const path		source;
};


