#pragma once

#include "engine/namespace.h"
#include "engine/old_model/vbo.h"

class				engine::eab :
					public engine::vbo<unsigned int, 1, engine::memory_management::static_draw>
{
public :
					eab() = default;
					~eab() override = default;

	void			use(bool state) const override
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state ? object : 0);
	}

	void			save() override
	{
		use(true);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(unsigned int) * std::vector<unsigned int>::size(),
			std::vector<unsigned int>::data(),
			GL_STATIC_DRAW);
		use(false);
	}
};
