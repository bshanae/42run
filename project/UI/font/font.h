#pragma once

#include "UI/namespace.h"

#include "UI/font/symbol.h"

class						UI::font::font :
								public enable_shared_from_this<UI::font::font>
{
	friend class			UI::font::renderer;
	friend class			UI::font::reader;

public :
							font(const path &source, const int &width, const vec3 &color);
							~font() = default;

	void					build_map();

private :

	static constexpr int	size_of_map = 128;

	FT_Face					face = nullptr;

	using 					map_type = map<char, shared<symbol>>;
	map_type				map;

	const vec3				color;

	shared<symbol>			build_symbol(char task);
	shared<symbol>			find_symbol(char task) const;
};


