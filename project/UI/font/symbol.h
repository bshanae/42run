#pragma once

#include "UI/namespace.h"

#include "UI/widget/widget.h"

class					UI::font::symbol : public UI::widget
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
};


