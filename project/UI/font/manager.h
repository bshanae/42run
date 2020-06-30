#pragma once

#include "UI/namespace.h"

class				UI::font::manager : public global<UI::font::manager>
{
	friend class 	font;

public :
					manager()
	{
		if (FT_Init_FreeType(&library))
			error::raise(error::id::freetype_library_error);
	}
					~manager()
	{
		FT_Done_FreeType(library);
	}

private :

	FT_Library		library;
};


