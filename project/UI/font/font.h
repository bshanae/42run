#pragma once

#include "UI/namespace.h"

#include "UI/font/symbol.h"

class						UI::font::font
{
public :
							font(const path &source, const int &width, const vec3 &color);

	const_shared<symbol>	find_symbol(char task) const;

private :

	static constexpr int	size_of_map = 128;

	FT_Face					face;

	using 					map_type = map<char, shared<symbol>>;
	map_type				map;

	const vec3				color;

	shared<symbol>			build_symbol(char task);
};


