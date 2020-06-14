#pragma once

#include "engine/namespace.h"

#include "engine/scene/camera.h"
#include "engine/scene/light.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class					engine::scene::scene
{
	friend class		engine::renderer;

private :
						scene() = default;
public :
						~scene() = default;

START_GLOBAL_CUSTOM_INITIALIZER(scene)
	connect_to_global();
	instance()->lights.reserve(SHARED_LIGHTS_CAPACITY);
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void			target(const model::model::ptr &target);
	static void			target(const model::instance::ptr &target);
	static void			target(const model::group::ptr &target);

	template			<typename ...args_type>
	static void			light(args_type ...args)
	{
		shared_ptr<scene>	instance = scene::instance();

		if (instance->lights.size() == SHARED_LIGHTS_CAPACITY)
		{
			warning::raise(warning::id::renderer_no_space_for_light);
			return ;
		}
		else
			instance->lights.push_back(engine::scene::light::make_ptr(args...));
	}

private :

IMPLEMENT_GLOBAL_INSTANCER(scene)

	static void			connect_to_global();

	camera				camera;

	using				lights_type = vector<engine::scene::light::ptr>;
	lights_type			lights;

	struct
	{
		using			models_type = vector<model::model::ptr>;
		using			instances_type = vector<model::instance::ptr>;
		using			groups_type = vector<model::group::ptr>;

		models_type		models;
		instances_type	instances;
		groups_type		groups;
	}					targets;
};