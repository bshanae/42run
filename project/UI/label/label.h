#pragma once

#include "UI/namespace.h"

#include "UI/font/font.h"
#include "UI/font/reader.h"

class					UI::label :
							public engine::game_object::game_object,
							public UI::font::reader
{
public :

	explicit			label
						(
							const ivec2 &position,
							const string &text,
							const shared<font::font> font
						) :
							position(position),
							text(text),
							font(font)

	{
		for (char character : text)
		{
			auto		symbol = font::reader::find_symbol(font, character);

			size.x += font::reader::advance(symbol);
			size.y = max(size.y, font::reader::size(symbol).y);
		}
	}
						~label() override = default;
private :

	ivec2				position;
	ivec2				size;
	string				text;

	shared<font::font>	font;
};