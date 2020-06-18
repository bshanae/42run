#include "renderer.h"

#include "engine/core/core.h"

using namespace				engine;

void						renderer::connect_with_global()
{
	shared_ptr<renderer>	instance = renderer::instance();

	global().renderer = instance;

	instance->on_press = interface::callback(interface::event::type::key_press, &renderer::callback, &*instance);
	instance->on_hold = interface::callback(interface::event::type::key_hold, &renderer::callback, &*instance);

	core::use_callback(instance->on_press);
	core::use_callback(instance->on_hold);
}