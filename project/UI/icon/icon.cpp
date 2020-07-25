#include "icon.h"

using namespace		UI;

					icon::icon::icon(const vec2 &position, const vec2 &size, const string &source)
{
	auto			texture = make_unique<model::texture>(source);
	auto			absolute_size = converter::to_absolute(size);

	build(texture);
	instance->scale(vec3(absolute_size.x, absolute_size.y, 1.f));
	change_position(position);
}

void				icon::icon::change_position(const vec2 &position)
{
	auto			new_position = converter::to_absolute(position);

	instance->reset_translation();
	instance->translate(vec3(new_position.x, new_position.y, 0.f));
}