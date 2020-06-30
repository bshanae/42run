#pragma once

#include "engine/namespace.h"

class 				engine::abstract::OpenGL_wrapper
{
protected :
					OpenGL_wrapper() = default;
public :

	virtual			~OpenGL_wrapper() = default;

	virtual void	use(bool state)
	{
		error::raise(error::id::unimplemented_virtual_method);
	}

protected :

	GLuint			object = 0;
};