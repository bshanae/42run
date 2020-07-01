#include "label.h"

using namespace		UI;

					label::label::label(const ivec2 &position, const string &text) :
						engine::game_object::game_object(tag<UI::label::renderer>()),
						position(position),
						text(text)
{
	size = ivec2(0);

	for (char character : text)
	{
		auto		symbol = font::reader::find_symbol(character);

		size.x += font::reader::advance(symbol);
		size.y = max(size.y, font::reader::size(symbol).y);
	}
}