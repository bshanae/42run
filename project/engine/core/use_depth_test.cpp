#include "core.h"

using namespace		engine;

void				core::use_depth_test(bool state)
{
	if (state)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}