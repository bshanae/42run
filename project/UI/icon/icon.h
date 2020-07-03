#pragma once

#include "UI/namespace.h"

class					UI::icon::icon : public engine::game_object::game_object
{
	friend class		UI::icon::renderer;

public :

	explicit			icon(const ivec2 &position, const path &source);
						~icon() override = default;
private :

	ivec2				position;
	ivec2				size;

	shared<rectangle>	rectangle;
};


