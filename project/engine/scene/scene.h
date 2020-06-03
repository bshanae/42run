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
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void			target(const model::model::ptr &target);
	static void			target(const model::instance::ptr &target);
	static void			target(const model::group::ptr &target);

	template			<typename ...args_type>
	static void			light(args_type ...args)
	{
		shared_ptr<scene>	instance = scene::instance();

		if (instance->lights_size == SHARED_LIGHTS_CAPACITY)
		{
			warning::raise(warning::id::renderer_no_space_for_light);
			return ;
		}
		else
			instance->lights[instance->lights_size++] = engine::scene::light(args...);
	}

private :

IMPLEMENT_GLOBAL_INSTANCER(scene)

	static void			connect_to_global();

	camera				camera;

	using				lights_type = array<engine::scene::light, SHARED_LIGHTS_CAPACITY>;
	lights_type			lights;
	int					lights_size = 0;

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