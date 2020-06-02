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
									renderer()
	{
		program = engine::program::program::make_ptr
		(
			settings().glsl_path / "main.vertex.glsl",
			settings().glsl_path / "main.fragment.glsl"
		);

		initialize_data();
	}

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
		empty = SHARED_LIGHT_TYPE_EMPTY,
		directional = SHARED_LIGHT_TYPE_DIRECTIONAL,
		point = SHARED_LIGHT_TYPE_POINT
	};

	static void 					light(
									light_type type,
									const vec3 &data,
									const vec3 &color,
									float intensity)
	{
		auto						&light_data = instance()->light_data;

		if (light_data.size == SHARED_LIGHTS_CAPACITY)
		{
			common::warning::raise(common::warning::id::renderer_no_space_for_light);
			return ;
		}

		light_data.type[light_data.size] = type;
		light_data.data[light_data.size] = data;
		light_data.color[light_data.size] = color;
		light_data.intensity[light_data.size] = intensity;

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

	void							initialize_data();

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
		light_type					type[SHARED_LIGHTS_CAPACITY] = {};
		vec3						data[SHARED_LIGHTS_CAPACITY] = {vec3(0.f)};
		vec3						color[SHARED_LIGHTS_CAPACITY] = {vec3(0.f)};
		float						intensity[SHARED_LIGHTS_CAPACITY] = {0.f};
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
			uniform_int				type[SHARED_LIGHTS_CAPACITY];
			uniform_vec3			data[SHARED_LIGHTS_CAPACITY];
			uniform_vec3			color[SHARED_LIGHTS_CAPACITY];
			uniform_float			intensity[SHARED_LIGHTS_CAPACITY];
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