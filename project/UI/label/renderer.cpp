#include "renderer.h"

#include "UI/rectangle/rectangle.h"
#include "UI/label/label.h"

using namespace		UI;

void				label::renderer::render(const shared<engine::game_object::game_object> &object) const
{
	auto			label = dynamic_pointer_cast<class label>(object);

	if (not label)
	{
		warning::raise(warning::id::object_is_not_a_label);
		return ;
	}

	ivec2			position_iterator = label->position;
	vec3			position_of_symbol = vec3(0.f);

	position_iterator.x -= label->size.x / 2;
	position_iterator.y += label->size.y / 2;

	for (char character : label->text)
	{
		auto		symbol = font::reader::find_symbol(character);
		auto		rectangle = font::reader::rectangle(symbol);

		auto		size = font::reader::size(symbol);
		auto		bearing = font::reader::bearing(symbol);
		auto		advance = font::reader::advance(symbol);

		position_of_symbol.x = (float)(position_iterator.x + bearing.x) + (float)size.x / 2.f;
		position_of_symbol.y = (float)(position_iterator.y - bearing.y) + (float)size.y / 2.f;

		rectangle->instance->reset_translation();
		rectangle->instance->translate(position_of_symbol);

		rectangle->render();

		position_iterator.x += advance;
	}
}