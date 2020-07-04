#include "icon.h"

#include "UI/icon/renderer.h"

using namespace		UI;

					icon::icon::icon(const vec2 &position, const path &source) :
						widget(tag<UI::icon::renderer>())
{
	auto			texture = make_unique<model::texture>(source);
	auto			size = texture->read_size();

	set_texture(texture);
	instance->scale(vec3(size.x * 0.5, size.y * 0.5, 1.f));
	reposition(position);
}

void				icon::icon::reposition(const vec2 &position)
{
	auto			new_position = converter::to_absolute(position);

	instance->reset_translation();
	instance->translate(vec3(new_position.x, new_position.y, 0.f));
}