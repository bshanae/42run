#include "core.h"

using namespace		engine;

float				core::time()
{
	return (glfwGetTime());
}

float				core::time_delta(bool normalize)
{
	return (instance()->last_time_delta / (normalize ? time_delta_normal : 1.f));
}