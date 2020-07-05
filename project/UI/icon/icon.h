#pragma once

#include "UI/namespace.h"

class					UI::icon::icon : public engine::game_object::game_object
{
	friend class		UI::icon::renderer;

public :

	explicit			icon(const vec2 &position, const path &source);
						~icon() override = default;

	void				reposition(const vec2 &position);

private :

	shared<rectangle>	rectangle;
};


