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

	void					exclude(const shared<light> &light);
	void					exclude(const shared<game_object::game_object> &light);

private :

	void					prepare();

	shared<camera>			camera = make_shared<engine::scene::camera>();

	using					lights_type = vector<shared<engine::scene::light>>;
	using					lights_iterator = lights_type::iterator;

	lights_type				lights;

	lights_type				lights_to_include;
	lights_type				lights_to_exclude;

	using					objects_type = vector<shared<game_object::game_object>>;
	using					objects_iterator = objects_type::iterator;

	objects_type			objects;

	objects_type			objects_to_include;
	objects_type			objects_to_exclude;

	bool					lights_have_changed = false;
	bool					objects_have_changed = false;
};