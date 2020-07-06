#pragma once

#include "UI/namespace.h"

#include "UI/font/reader.h"

class					UI::label::label :
							public engine::game_object::game_object,
							public UI::font::reader
{
	friend class		UI::label::renderer;

public :
						label
						(
							const vec2 &position,
							const string &text,
							const shared<font::font> &font,
							alignment alignment = alignment::center
						);
						~label() override = default;

	void				change_text(const string &text);

private :

	ivec2				position;
	shared<font::font>	font;
	enum alignment		alignment;

	string				text;
	ivec2				text_position;
};