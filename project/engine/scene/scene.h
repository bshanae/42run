#pragma once

#include "engine/namespace.h"

#include "engine/scene/camera.h"
#include "engine/scene/light.h"
#include "engine/game_object/game_object.h"

class						engine::scene::scene
{
	friend class			engine::core;
	friend class			engine::renderer;

private :
							scene() = default;
public :
							~scene() = default;

START_GLOBAL_CUSTOM_INITIALIZER(scene)
	instance(false) = shared_ptr<scene>(new scene());
	connect_to_global();
	instance()->lights.reserve(SHARED_LIGHTS_CAPACITY);
FINISH_GLOBAL_CUSTOM_INITIALIZER

	template				<typename ...args_type>
	static void				light(args_type ...args)
	{
		shared_ptr<scene>	instance = scene::instance();

		if (instance->lights.size() == SHARED_LIGHTS_CAPACITY)
			warning::raise(warning::id::renderer_no_space_for_light);
		else
			instance->lights.push_back(engine::scene::light::make_ptr(args...));
	}

	template				<typename type, typename ...args_type>
	static auto				game_object(args_type ...args)
	{
		if constexpr (not std::is_base_of<engine::game_object, type>::value)
			error::raise(error::id::scene_bad_game_object_parent);

		shared_ptr<scene>	instance = scene::instance();
		auto				pointer = type::make_ptr(args...);

		instance->objects_to_add.push_back(static_pointer_cast<engine::game_object>(pointer));
		return (pointer);
	}

	template				<typename type>
	static void				forget(const shared_ptr<type> &child)
	{
		if constexpr (not std::is_base_of<engine::game_object, type>::value)
			error::raise(error::id::scene_bad_game_object_parent);

		auto				parent = static_pointer_cast<engine::game_object>(child);

		parent->enable(false);
		instance()->objects_to_delete.push_back(parent);
	}

private :

IMPLEMENT_GLOBAL_INSTANCER(scene)

	static void				connect_to_global()
	{
		global().scene = instance();
	}

	void					process_game_objects()
	{
		for (auto &object_to_add : objects_to_add)
			objects.push_back(object_to_add);

		objects_iterator	iterator;

		for (auto &object_to_delete : objects_to_delete)
		{
			iterator = find(objects.begin(), objects.end(), object_to_delete);

			if (iterator != objects_to_delete.end())
				objects.erase(iterator);
		}

		objects_to_add.clear();
		objects_to_delete.clear();
	}

	camera					camera;

	using					lights_type = vector<engine::scene::light::ptr>;
	lights_type				lights;

	using					objects_type = vector<engine::game_object::ptr>;
	using					objects_iterator = objects_type::iterator;

	objects_type			objects;
	objects_type			objects_to_add;
	objects_type			objects_to_delete;
};