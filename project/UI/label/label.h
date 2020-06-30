#pragma once

#include "UI/namespace.h"

#include "UI/font/reader.h"
#include "UI/label/renderer.h"

class					UI::label::label :
							public engine::game_object::game_object,
							public UI::font::reader
{
	friend class		UI::label::renderer;

public :

	explicit			label
						(
							const ivec2 &position,
							const string &text,
							const shared<font::font> font
						);
						~label() override = default;
private :

	ivec2				position;
	ivec2				size;
	string				text;

	shared<font::font>	font;
};