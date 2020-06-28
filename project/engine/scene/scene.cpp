#include "scene.h"

using namespace		engine;

void					scene::scene::include(const shared<light> &light)
{
	lights_to_include.push_back(light);
}

void					scene::scene::include(const shared<game_object::game_object> &object)
{
	objects_to_include.push_back(object);
}

void					scene::scene::prepare()
{
//						Lights
	lights_have_changed = not lights_to_include.empty();

	for (auto &light_to_add : lights_to_include)
		lights.push_back(light_to_add);
	lights_to_include.clear();

//						Objects
	objects_have_changed = not objects_to_include.empty();

	for (auto &object_to_add : objects_to_include)
		objects.push_back(object_to_add);
	objects_to_include.clear();

	objects.remove_if
	(
		[](const shared<game_object::game_object> &object)
		{
			return (object->state == game_object::state::stopped);
		}
	);
}
