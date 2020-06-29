#pragma once

#include "engine/namespace.h"

#include "engine/program/program.h"
#include "engine/model/reader.h"
#include "engine/game_object/reader.h"
#include "engine/scene/reader.h"

class							engine::renderer :
									public engine::model::reader,
									public engine::game_object::reader,
									public engine::scene::reader
{
	friend class				engine::core;
	friend class				engine::game_object::game_object;

protected :
								renderer(const path &vertex, const path &fragment)
	{
		program = make_unique<program::program>(vertex, fragment);
	}

public :

	virtual						~renderer() = default;

protected :

	virtual void				render(const shared<engine::game_object::game_object> &object) const = 0;

	unique<program::program>	program;

	using 						uniform_int = program::uniform<int>;
	using 						uniform_float = program::uniform<float>;
	using 						uniform_vec3 = program::uniform<vec3>;
	using 						uniform_vec4 = program::uniform<vec4>;
	using 						uniform_mat4 = program::uniform<mat4>;
};