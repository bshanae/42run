#include "core.h"

#include "engine/renderer/renderer.h"

using namespace		engine;

void				core::connect_renderer()
{
	 auto			&renderer = engine::renderer::instance();

	core::instance()->renderer = renderer;
	generate_callback(interface::event::type::key_press, &renderer::callback, &*renderer);
	generate_callback(interface::event::type::key_hold, &renderer::callback, &*renderer);
}