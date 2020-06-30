#include "core.h"

using namespace		engine;

void				core::show_polygon_back(bool state)
{
	if (state)
		glDisable(GL_CULL_FACE);
	else
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
}