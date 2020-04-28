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
		if (first - last != std::vector<type>::size())
			resize((last - first) / group);

		type		*target = std::vector<type>::data();

		do
			*target++ = *first++;
		while (first != last);

	}

	void 			resize(int size)
	{
		if (not already_resized)
			already_resized = true;
		else
			throw (exception::make_object<exception::id::VBO_resize_more_than_one>());

		std::vector<type>::resize(size * group);
	}

	int 			size()
	{
		return (std::vector<type>::size() / group);
	}

	virtual void	save()
	{
		if constexpr (management == memory_management::static_draw)
			if (already_saved)
				throw (exception::make_object<exception::id::VBO_static>());

		use(true);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(type) * std::vector<type>::size(),
			std::vector<type>::data(),
			static_cast<GLuint>(management));
		use(false);

		already_saved = true;
	}

private :

	bool			already_resized = false;
	bool			already_saved = false;
};
