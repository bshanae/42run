#pragma once

#include "engine/namespace.h"
#include "engine/object_wrap/object_wrap.h"

template			<typename type, int group, engine::memory_management management>
class				engine::vbo : public object_wrap, protected std::vector<type>
{
public :
					vbo()
	{
		glGenBuffers(1, &object);
	}

					~vbo() override
	{
		glDeleteBuffers(1, &object);
	}

	void			use(bool state) const override
	{
		glBindBuffer(GL_ARRAY_BUFFER, state ? object : 0);
	}

	type			&at(int index)
	{
		return (std::vector<type>::at(index * group));
	}


	void			copy(type *first, type *last)
	{
		resize(last - first);

		type		*target = std::vector<type>::data();

		do
			*target++ = *first++;
		while (first != last);

	}

	void 			resize(int size)
	{
		std::vector<type>::resize(size * group);
	}

	int 			size()
	{
		return (std::vector<type>::size() / group);
	}

	virtual void	save()
	{
		use(true);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(type) * std::vector<type>::size(),
			std::vector<type>::data(),
			static_cast<GLuint>(management));
		use(false);
	}
};
