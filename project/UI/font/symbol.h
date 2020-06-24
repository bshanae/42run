#pragma once

#include "UI/namespace.h"

class				UI::font::symbol
{
	friend class	UI::font::font;

private :
					symbol(FT_Face &face);
public :
					~symbol();
private :

IMPLEMENT_CONST_SHARED_POINTER_FUNCTIONALITY(symbol)

	GLuint			texture;

	ivec2			size;
	ivec2			bearing;
	int				advance;
};


