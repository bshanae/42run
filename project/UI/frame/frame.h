#pragma once

#include "UI/namespace.h"

class								UI::frame::frame : public engine::game_object::game_object
{
	friend class					UI::frame::renderer;

public :
									frame
									(
										const vec2 &position,
										const vec2 &size,
										const vec3 &color,
										float border_size = 0.f,
										const vec3 &border_color = vec3(0.f)
									);
									~frame() override = default;
private :

	shared<rectangle::rectangle>	front;
	shared<rectangle::rectangle>	back;
};


