#include "icon.h"

using namespace		UI;

					icon::icon::icon(const vec2 &position, const path &source)
{
	auto			texture = make_unique<model::texture>(source);
	auto			size = texture->read_size();

	build(texture);
	instance->scale(vec3(size.x * 0.5, size.y * 0.5, 1.f));
	instance->scale(engine::settings().window_scaling.x);
	change_position(position);
}

void				icon::icon::change_position(const vec2 &position)
{
	auto			new_position = converter::to_absolute(position);

	instance->reset_translation();
	instance->translate(vec3(new_position.x, new_position.y, 0.f));
}