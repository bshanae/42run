#pragma once

#include "UI/namespace.h"

class				UI::font::symbol
{
	friend class	UI::font::font;

public :
					symbol(FT_Face &face);
					~symbol();
private :

	GLuint			texture;

	ivec2			size;
	ivec2			bearing;
	int				advance;
};


