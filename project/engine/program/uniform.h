#pragma once

#include "engine/namespace.h"

#include "engine/object_wrap/object_wrap.h"

template 			<typename type>
class 				engine::program::uniform : public engine::object_wrap
{
	friend class	engine::program::program;

public :

					uniform() = default;
					~uniform() override = default;

	void			save(const type &data)
	{
		if (object == -1)
			throw (exception::make_object<exception::id::uniform_value>());
		if constexpr (std::is_same<type, int>::value)
			glUniform1i(object, data);
		else if constexpr (std::is_same<type, float>::value)
			glUniform1f(object, data);
		else if constexpr (std::is_same<type, glm::vec3>::value)
			glUniform3f(object, data.x, data.y, data.z);
		else if constexpr (std::is_same<type, glm::vec4>::value)
			glUniform4f(object, data.x, data.y, data.z, data.w);
		else if constexpr (std::is_same<type, glm::mat4>::value)
			glUniformMatrix4fv(object, 1, GL_FALSE, value_ptr(data));
		else
			throw (exception::make_object<exception::id::uniform_type>());
	}

private :

	explicit		uniform(GLuint value)
	{
		object = value;
	}
};