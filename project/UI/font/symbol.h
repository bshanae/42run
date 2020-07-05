#pragma once

#include "UI/namespace.h"

class					UI::font::symbol
{
	friend class		UI::font::font;
	friend class		UI::font::reader;

public :
						symbol(FT_Face &face);
						~symbol() = default;
private :

	ivec2				size;
	ivec2				bearing;
	int					advance;

	shared<rectangle>	rectangle;
};


