#include "renderer.h"

using namespace		engine;

void				renderer::animate()
{
	global().revise();

	for (const auto &object : global().scene->objects)
		for (const auto &animation_target : object->animation_targets)
			animation_target->skeleton->update();
}