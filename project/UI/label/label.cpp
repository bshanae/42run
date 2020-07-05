#include "label.h"

#include "UI/label/renderer.h"

using namespace		UI;

					label::label::label
					(
						const vec2 &position,
						const string &text,
						enum alignment alignment
					) :
						engine::game_object::game_object(tag<UI::label::renderer>()),
						position(converter::to_absolute(position)),
						alignment(alignment),
						text(text)
{
	change_text(text);
}

void				label::label::change_text(const string &text)
{
	auto			size = ivec2(0);

	for (char character : text)
	{
		auto		symbol = font::reader::find_symbol(character);

		size.x += font::reader::advance(symbol);
		size.y = max(size.y, font::reader::size(symbol).y);
	}

	text_position = position;
	text_position.y += size.y;
	switch (alignment)
	{
		case alignment::center :
			text_position.x -= size.x / 2;
			break ;

		case alignment::left :
			break ;

		case alignment::right :
			text_position.x -= size.x;
			break ;
	}
}

