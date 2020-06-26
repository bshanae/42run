#include "scene.h"

using namespace		engine;

void					scene::scene::include(const shared<light> &light)
{
	lights_to_include.push_back(light);
	have_changed = true;
}

void					scene::scene::include(const shared<game_object::game_object> &object)
{
	objects_to_include.push_back(object);
	have_changed = true;
}

void					scene::scene::exclude(const shared<light> &light)
{
	lights_to_exclude.push_back(light);
	have_changed = true;
}

void					scene::scene::exclude(const shared<game_object::game_object> &object)
{
	objects_to_exclude.push_back(object);
	have_changed = true;
}

void					scene::scene::prepare()
{
//						Lights
	for (auto &light_to_add : lights_to_include)
		lights.push_back(light_to_add);

	lights_iterator		light_iterator;

	for (auto &light_to_delete : lights_to_exclude)
	{
		light_iterator = find(lights.begin(), lights.end(), light_to_delete);
		if (light_iterator != lights_to_exclude.end())
			lights.erase(light_iterator);
	}

	lights_to_include.clear();
	lights_to_exclude.clear();

//						Objects
	for (auto &object_to_add : objects_to_include)
		objects.push_back(object_to_add);

	objects_iterator	object_iterator;

	for (auto &object_to_delete : objects_to_exclude)
	{
		object_iterator = find(objects.begin(), objects.end(), object_to_delete);
		if (object_iterator != objects_to_exclude.end())
			objects.erase(object_iterator);
	}

	objects_to_include.clear();
	objects_to_exclude.clear();
}
