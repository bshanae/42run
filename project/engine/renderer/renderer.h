#pragma once

#include "engine/namespace.h"

#include "engine/core/core.h"
#include "engine/program/program.h"
#include "engine/scene/scene.h"
#include "engine/model/skeleton.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class								engine::renderer
{
	friend class					core;

private :
									renderer();
public :
	virtual							~renderer() = default;
public :

START_GLOBAL_CUSTOM_INITIALIZER(renderer)
	engine::core::connect_renderer();
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void						target(const model::instance::ptr &target)
	{
		instance()->targets.instances.push_back(target);
	}

	static void						target(const model::group::ptr &target)
	{
		instance()->targets.groups.push_back(target);
	}

	bool							request = true;

	enum class 						light_type : int
	{
		directional = 0,
		point = 1
	};

	static void 					light(light_type type, vec3 data, vec3 color)
	{
		auto						&light_data = instance()->light_data;

		if (light_data.size == SHARED_LIGHTS_CAPACITY)
		{
			common::warning::raise(common::warning::id::renderer_no_space_for_light);
			return ;
		}

		light_data.direction_or_position[light_data.size].x = data.x;
		light_data.direction_or_position[light_data.size].y = data.y;
		light_data.direction_or_position[light_data.size].z = data.z;
		light_data.direction_or_position[light_data.size].w = (float)(int)type;

		light_data.color[light_data.size] = color;

		light_data.size++;
	}

private :

IMPLEMENT_GLOBAL_INSTANCER(renderer)

	struct
	{
		using						instances_type = vector<model::instance::ptr>;
		using						groups_type = vector<model::group::ptr>;

		instances_type				instances;
		groups_type					groups;
	}								targets;

	void 							upload_camera_data();
	void 							upload_light_data();

	void							render();
	void							render(const model::instance::ptr &instance);
	void							render(const model::group::ptr &group);

	void							callback();

	engine::program::program::ptr	program;
	engine::scene::scene			scene;

	struct
	{
		int							size = 0;
		vec4						direction_or_position[SHARED_LIGHTS_CAPACITY];
		vec3						color[SHARED_LIGHTS_CAPACITY];
	}								light_data;

	using 							uniform_int = engine::program::uniform<int>;
	using 							uniform_float = engine::program::uniform<float>;
	using 							uniform_vec3 = engine::program::uniform<vec3>;
	using 							uniform_vec4 = engine::program::uniform<vec4>;
	using 							uniform_mat4 = engine::program::uniform<mat4>;

	struct							texture_wrap
	{
		uniform_int 				is_valid;
		uniform_int 				value;
	};

	struct
	{
		uniform_mat4				projection;
		uniform_mat4				view;

		struct
		{
			struct
			{
				uniform_vec3		ambient;
				uniform_vec3		diffuse;
				uniform_vec3		specular;
				uniform_vec3		emission;
				uniform_float		alpha;
			}						unite;

			struct
			{
				texture_wrap		ambient;
				texture_wrap		diffuse;
				texture_wrap		specular;
			}						textures;
		}							material;

		uniform_vec3				camera_position;

		struct
		{
			uniform_int				size;
			uniform_vec4			direction_or_position[SHARED_LIGHTS_CAPACITY];
			uniform_vec3			color[SHARED_LIGHTS_CAPACITY];
		}							light;

		uniform_int 				does_mesh_have_bones;
		uniform_mat4 				bones_transformations[model::skeleton::bones_limit];

		struct
		{
			uniform_mat4			scaling;
			uniform_mat4			translation;
			uniform_mat4			rotation;
		}							instance;

		struct
		{
			uniform_mat4			scaling;
			uniform_mat4			translation;
			uniform_mat4			rotation;
		}							group;
	}								uniforms;
};