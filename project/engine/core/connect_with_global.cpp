#include "core.h"

using namespace		engine;

void				core::connect_with_global()
{
	global().core = instance();
}