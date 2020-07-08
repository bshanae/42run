#include "frame.h"

#include "UI/rectangle/rectangle.h"
#include "UI/frame/renderer.h"

using namespace		UI;

					frame::frame::frame
					(
						const vec2 &position,
						const vec2 &size,
						const vec3 &color,
						float border_size,
						const vec3 &border_color
					) :
						game_object(tag<UI::frame::renderer>())
{
	vec2			absolute_position = converter::to_absolute(position);

	vec2			front_size;
	vec2			back_size;

	back_size = converter::to_absolute(size);
	front_size = back_size * (1.f - border_size);

	front = make_shared<rectangle::rectangle>();
	front->build(color);
	front->start();
	front->instance->scale(vec3(front_size.x * 0.5f, front_size.y * 0.5f, 1.f));
	front->instance->translate(vec3(absolute_position.x, absolute_position.y, -0.00001f));

	back = make_shared<rectangle::rectangle>();
	back->build(border_color);
	back->start();
	back->instance->scale(vec3(back_size.x * 0.5, back_size.y * 0.5, 1.f));
	back->instance->translate(vec3(absolute_position.x, absolute_position.y, -0.00002f));
}