#pragma once

#include "game/namespace.h"

#include "game/model_with_mods/instance.h"

class				game::model_with_mods::group : public engine::model::group
{
public :

	void			hollow(bool state)
	{
		for (auto &instance : instances)
			if (auto instance_with_mods = dynamic_pointer_cast<model_with_mods::instance>(instance))
				instance_with_mods->hollow(state);
	}

	shared<group>	copy() const
	{
		auto		result = make_shared<group>();

		for (auto &instance : instances)
			if (auto instance_with_mods = dynamic_pointer_cast<model_with_mods::instance>(instance))
				result->instances.push_back(instance_with_mods->copy());

		result->data = data;
		result->transformations = transformations;

		return (result);
	}
};