#pragma once

#include "engine/namespace.h"

#include "engine/scene/camera.h"
#include "engine/scene/light.h"
#include "engine/game_object/game_object.h"

class						engine::scene::scene
{
	friend class			engine::core;
	friend class			engine::scene::reader;

public :
							scene() = default;
							~scene() = default;

	void					include(const shared<light> &light);
	void					include(const shared<game_object::game_object> &light);

	void					background(const vec3 &value)
	{
		background_value = value;
	}

private :

	vec3					background_value = vec3(0);

	void					prepare();

	shared<camera>			camera = make_shared<engine::scene::camera>();

	using					lights_type = vector<shared<engine::scene::light>>;
	using					lights_iterator = lights_type::iterator;

	lights_type				lights;
	lights_type				lights_to_include;

	using					objects_type = list<shared<game_object::game_object>>;
	using					objects_iterator = objects_type::iterator;

	objects_type			objects;
	objects_type			objects_to_include;

	bool					lights_have_changed = false;
	bool					objects_have_changed = false;
};