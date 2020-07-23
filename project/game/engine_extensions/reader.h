#pragma once

#include "game/namespace.h"

#include "game/engine_extensions/instance.h"

class				game::engine_extensions::reader
{
protected :

	[[nodiscard]]
	inline bool		hollow(const shared<engine_extensions::instance> &instance) const
	{
		return (instance->mods.hollow);
	}

	[[nodiscard]]
	inline bool		color_mix_state(const shared<engine_extensions::instance> &instance) const
	{
		return (instance->mods.color_mix.state);
	}

	[[nodiscard]]
	inline float	color_mix_factor(const shared<engine_extensions::instance> &instance) const
	{
		return (instance->mods.color_mix.factor);
	}

	[[nodiscard]]
	inline vec4		color_mix_color(const shared<engine_extensions::instance> &instance) const
	{
		return (instance->mods.color_mix.color);
	}
};