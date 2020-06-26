#pragma once

#include "UI/namespace.h"

#include "UI/font/font.h"

class				UI::label : engine::game_object
{
public :

	explicit		label
					(
						const ivec2 &position,
						const string &text,
						const font::font::ptr font
					);
					~label() override = default;
private :

	ivec2			position;
	ivec2			size;
	string			text;
};