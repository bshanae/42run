#pragma once

#include "UI/namespace.h"

#include "UI/font/symbol.h"

class						UI::font::font :
								public enable_shared_from_this<UI::font::font>
{
	friend class			UI::font::renderer;
	friend class			UI::font::reader;

public :
							font(const string &source, const int &width, const vec3 &color = vec3(1.f));
							~font() = default;

	void					build_map();
	void					change_color(const vec3 &color);

private :

	static constexpr int	size_of_map = 128;

	FT_Face					face = nullptr;

	using 					map_type = map<char, shared<symbol>>;
	map_type				map;

	vec3					color;

	shared<symbol>			build_symbol(char task);
	shared<symbol>			find_symbol(char task) const;
};


