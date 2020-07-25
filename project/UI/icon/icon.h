#pragma once

#include "UI/namespace.h"

#include "UI/rectangle/rectangle.h"

class					UI::icon::icon :
							public UI::rectangle::rectangle
{
public :
						icon(const vec2 &position, const vec2 &size, const string &source);
						~icon() override = default;

	void				change_position(const vec2 &position);
};