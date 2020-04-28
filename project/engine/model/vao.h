#pragma once

#include "engine/namespace.h"
#include "engine/model/vbo.h"

class 						engine::vao : public engine::object_wrap
{
public :
							vao()
	{
		glGenVertexArrays(1, &object);
	}
							~vao() override
	{
		glDeleteVertexArrays(1, &object);
	}

	void 					use(bool state) const override
	{
		glBindVertexArray(state ? object : 0);
	}

	template				<typename type, int group, engine::memory_management management>
	void					connect(const vbo<type, group, management> &vbo)
	{
		vbo.use(true);
		glVertexAttribPointer(
			counter,
			group,
			convert_type<type>(),
			GL_FALSE,
			sizeof(type) * group,
			nullptr);
		glEnableVertexAttribArray(counter++);
		vbo.use(false);
	}

private :

	int						counter = 0;

	template				<typename type>
	[[nodiscard]] GLuint	convert_type() const
	{
		if constexpr (std::is_same<type, unsigned int>::value)
			return (GL_UNSIGNED_INT);
		else if constexpr (std::is_same<type, float>::value)
			return (GL_FLOAT);
		else
			throw (exception::make_object<exception::id::VAO_type>());
	}
};