#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_wrapper.h"

class				engine::model::texture : public engine::abstract::OpenGL_wrapper
{
	friend class	engine::model::reader;

public :
					texture();
	explicit		texture(const string &source);

					~texture() override;

	void			use(bool state) override;

	[[nodiscard]]
	auto			read_size() const
	{
		return (size);
	}

private :

	ivec2			size = ivec2(0);
};


