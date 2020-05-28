#pragma once

#include "engine/namespace.h"

class 				engine::abstract::object_wrap
{
protected :
					object_wrap() = default;
public :

	virtual			~object_wrap() = default;

	virtual void	use(bool state) const
	{
		common::error::raise(common::error::id::unimplemented_virtual_method);
	}

protected :

	GLuint			object = 0;
};