#include "font.h"

#include "UI/font/manager.h"

using namespace				UI;

							font::font::font(const path &source, const int &width, const vec3 &color) :
								color(color)
{
	auto					&library = manager::instance()->library;

	if (FT_New_Face(library, source.c_str(), 0, &face))
		error::raise(error::id::freetype_face_error);

	FT_Set_Pixel_Sizes(face, 0, width);
}

void						font::font::build_map()
{
	for (int i = 0; i < size_of_map; i++)
		map.emplace(i, build_symbol(static_cast<char>(i)));
}

void						font::font::change_color(const vec3 &color)
{
	this->color = color;
}

shared<font::symbol>		font::font::find_symbol(char task) const
{
	auto					result = map.find(task);

	if (result == map.end())
	{
		warning::raise(warning::id::font_symbol_not_found);
		return {};
	}
	else
		return (result->second);
}


shared<font::symbol>		font::font::build_symbol(char task)
{
	if (FT_Load_Char(face, task, FT_LOAD_RENDER))
		error::raise(error::id::freetype_symbol_error);

	shared<symbol>			new_symbol;

	new_symbol = make_shared<symbol>(face);
	new_symbol->font = shared_from_this();
	new_symbol->start();
	return (new_symbol);
}
