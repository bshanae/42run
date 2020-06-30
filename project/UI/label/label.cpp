#include "label.h"

using namespace		UI;

					label::label::label
					(
						const ivec2 &position,
						const string &text,
						const shared<font::font> font
					) :
						engine::game_object::game_object(tag<UI::label::renderer>()),
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