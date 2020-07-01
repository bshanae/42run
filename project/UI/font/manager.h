#pragma once

#include "UI/namespace.h"

class						UI::font::manager : public global<UI::font::manager>
{
	friend class 			UI::font::font;
	friend class 			UI::font::renderer;
	friend class 			UI::font::reader;

public :
							manager();
							~manager();

	static void				load(const path &source, const int &width, const vec3 &color);

private :

	FT_Library				library;
	shared<UI::font::font>	font;
};


