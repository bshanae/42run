#include "icon.h"

#include "UI/rectangle/rectangle.h"
#include "UI/icon/renderer.h"

using namespace		UI;

					icon::icon::icon(const vec2 &position, const path &source) :
						engine::game_object::game_object(tag<UI::icon::renderer>()),
						position(converter::to_absolute(position)),
						size(0)
{
	auto			texture = make_unique<model::texture>(source);

	size = texture->read_size();
	rectangle = make_shared<UI::rectangle>(tag<UI::icon::renderer>(), texture);
	rectangle->instance->scale(vec3(size.x * 0.5, size.y * 0.5, 1.f));
	rectangle->instance->translate(vec3(this->position.x, this->position.y, 0.f));
	rectangle->start();
}