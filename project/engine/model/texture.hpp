#pragma once

#include "engine/namespace.h"

class				engine::texture : public engine::object_wrap
{
	friend class	renderer;

public :

	explicit		texture(const path &source) :
					source(source)
	{
		glGenTextures(1, &object);

		int			width;
		int			height;
		int			number_of_components;

		auto		*data = stbi_load(source.c_str(), &width, &height, &number_of_components, 0);

		if (not data)
			throw (exception::make_object<exception::id::texture_creation>());

		GLenum		format;

		switch (number_of_components)
		{
			case 1 :
				format = GL_RED;
				break ;
			case 3 :
				format = GL_RGB;
				break ;
			case 4 :
				format = GL_RGBA;
				break ;
			default :
				throw (exception::make_object<exception::id::texture_format>());
		}

		glBindTexture(GL_TEXTURE_2D, object);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

					~texture()
	{
		glDeleteTextures(1, &object);
	}

	const path		source;
};


