#pragma once

#include "engine/namespace.h"

class 				engine::object_wrap
{
protected :
					object_wrap() = default;
public :

	virtual			~object_wrap() = default;

	virtual void	use(bool state) const
	{
		throw (exception::make_object<exception::id::unimplemented_virtual_method>());
	}

protected :

	GLuint			object = 0;
};