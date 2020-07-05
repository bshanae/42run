#pragma once

#include "UI/namespace.h"

#include "UI/rectangle/rectangle.h"

class					UI::icon::icon :
							public UI::rectangle::rectangle
{
public :

	explicit			icon(const vec2 &position, const path &source);
						~icon() override = default;

	void				reposition(const vec2 &position);
};


