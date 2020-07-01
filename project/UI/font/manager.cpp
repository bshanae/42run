#include "manager.h"

#include "UI/font/font.h"

using namespace		UI;

					font::manager::manager()
{
	if (FT_Init_FreeType(&library))
		error::raise(error::id::freetype_library_error);
}

					font::manager::~manager()
{
	FT_Done_FreeType(library);
}

void				font::manager::load(const path &source, const int &width, const vec3 &color)
{
	instance()->font = make_shared<UI::font::font>(source, width, color);
}
