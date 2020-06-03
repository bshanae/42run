#include "renderer.h"

#include "engine/core/core.h"

using namespace				engine;

void						renderer::connect_with_global()
{
	shared_ptr<renderer>	instance = renderer::instance();

	global().renderer = instance;

	core::generate_callback(interface::event::type::key_press, &renderer::callback, &*instance);
	core::generate_callback(interface::event::type::key_hold, &renderer::callback, &*instance);
}