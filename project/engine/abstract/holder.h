#pragma once

#include "engine/namespace.h"

class 				engine::abstract::holder
{
protected :
					holder() = default;
public :

	virtual			~holder() = default;

	virtual void	use(bool state) const
	{
		common::error::raise(common::error::id::unimplemented_virtual_method);
	}

protected :

	GLuint			object = 0;
};