#include "manager.h"

#include "UI/font/font.h"

using namespace		UI;

					font::manager::manager()
{
	if (FT_Init_FreeType(&library))
		error::raise(error::id::freetype_library_error);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

					font::manager::~manager()
{
	FT_Done_FreeType(library);
}