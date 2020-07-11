#pragma once

#include "game/namespace.h"

#include "game/model_with_mods/instance.h"

class				game::model_with_mods::reader
{
protected :

	[[nodiscard]]
	inline bool		hollow(const shared<model_with_mods::instance> &instance) const
	{
		return (instance->mods.hollow);
	}

	[[nodiscard]]
	inline bool		color_mix_state(const shared<model_with_mods::instance> &instance) const
	{
		return (instance->mods.color_mix.state);
	}

	[[nodiscard]]
	inline float	color_mix_factor(const shared<model_with_mods::instance> &instance) const
	{
		return (instance->mods.color_mix.factor);
	}

	[[nodiscard]]
	inline vec4		color_mix_color(const shared<model_with_mods::instance> &instance) const
	{
		return (instance->mods.color_mix.color);
	}
};