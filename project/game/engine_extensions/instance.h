#pragma once

#include "game/namespace.h"

class					game::engine_extensions::instance : public engine::model::instance
{
	friend class		game::engine_extensions::reader;

public :

	explicit			instance(const shared<engine::model::model> &model) :
							engine::model::instance(model)
						{}

	shared<instance>	copy() const
	{
		auto			result = make_shared<instance>(model);

		result->data = data;
		result->transformations = transformations;
		result->mods = mods;

		return (result);
	}

	void				hollow(bool state)
	{
		mods.hollow = state;
	}

	void				color_mix_state(bool state)
	{
		mods.color_mix.state = state;
	}

	void				color_mix_factor(float factor)
	{
		mods.color_mix.factor = factor;
	}

	void				color_mix_color(const vec3 &color)
	{
		mods.color_mix.color = vec4(color.x, color.y, color.z, 1.f);
	}

	void				color_mix_color(const vec4 &color)
	{
		mods.color_mix.color = color;
	}

protected :

	struct
	{
		bool			hollow = false;

		struct
		{
			bool		state = false;
			float		factor;
			vec4		color;
		}				color_mix;
	}					mods;
};
