#pragma once

#include "engine/namespace.h"

class 				engine::abstract::OpenGL_object
{
protected :
					OpenGL_object() = default;
public :

	virtual			~OpenGL_object() = default;

	virtual void	use(bool state) const
	{
		error::raise(error::id::unimplemented_virtual_method);
	}

protected :

	GLuint			object = 0;
};