#include "core.h"

using namespace		engine;

void				core::fill_polygon(bool state)
{
	glPolygonMode(GL_FRONT_AND_BACK, state ? GL_FILL : GL_LINE);
}