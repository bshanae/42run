#include "renderer.h"

#include "UI/rectangle/rectangle.h"
#include "UI/frame/frame.h"

using namespace		UI;

void				frame::renderer::render(const shared<engine::game_object::game_object> &object) const
{
	auto			frame = dynamic_pointer_cast<UI::frame::frame>(object);

	if (not frame)
	{
		warning::raise(warning::id::object_improper_type);
		return ;
	}

	frame->back->render();
	frame->front->render();
}