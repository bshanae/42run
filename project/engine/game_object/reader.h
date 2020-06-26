#pragma once

#include "engine/namespace.h"

#include "engine/game_object/game_object.h"

class 					engine::game_object::reader
{
public :
						reader() = default;
	virtual				~reader() = default;

protected :

	[[nodiscard]]
	inline const auto	&render_targets(const shared<engine::game_object::game_object> &object) const
	{
		return (object->render_targets);
	}

	[[nodiscard]]
	inline const auto	&animation_targets(const shared<engine::game_object::game_object> &object) const
	{
		return (object->animation_targets);
	}
};