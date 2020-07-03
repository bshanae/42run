#pragma once

#include "UI/namespace.h"

#include "UI/font/reader.h"

class					UI::label::label :
							public engine::game_object::game_object,
							public UI::font::reader
{
	friend class		UI::label::renderer;

public :
						label(const vec2 &position, const string &text);
						~label() override = default;
private :

	ivec2				position;
	ivec2				size;
	string				text;
};