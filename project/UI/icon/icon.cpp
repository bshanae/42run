#include "icon.h"

#include "UI/rectangle/rectangle.h"
#include "UI/icon/renderer.h"

using namespace		UI;

					icon::icon::icon(const vec2 &position, const path &source) :
						engine::game_object::game_object(tag<UI::icon::renderer>())
{
	auto			texture = make_unique<model::texture>(source);
	auto			size = texture->read_size();

	rectangle = make_shared<UI::rectangle>(tag<UI::icon::renderer>(), texture);
	rectangle->instance->scale(vec3(size.x * 0.5, size.y * 0.5, 1.f));
	rectangle->start();

	reposition(position);
}

void				icon::icon::reposition(const vec2 &position)
{
	auto			new_position = converter::to_absolute(position);

	rectangle->instance->reset_translation();
	rectangle->instance->translate(vec3(new_position.x, new_position.y, 0.f));
}