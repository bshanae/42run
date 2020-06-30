#include "core.h"

using namespace		engine;

void				core::use(const shared<scene::scene> &scene)
{
	instance()->scene = scene;
}

void				core::use(interface::callback &callback)
{
	instance()->callbacks.push_back(callback);
}

void				core::use(interface::timer &timer)
{
	instance()->timers.push_back(timer);
}