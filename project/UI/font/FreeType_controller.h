#pragma once

#include "UI/namespace.h"

class				UI::font::FreeType_controller
{
	friend class 	font;

public :
					FreeType_controller()
	{
		if (FT_Init_FreeType(&library))
			error::raise(error::id::freetype_library_error);
	}
					~FreeType_controller()
	{
		FT_Done_FreeType(library);
	}

START_GLOBAL_INITIALIZER(FreeType_controller)
FINISH_GLOBAL_INITIALIZER

private :

IMPLEMENT_GLOBAL_INSTANCER(FreeType_controller)

	FT_Library		library;
};


