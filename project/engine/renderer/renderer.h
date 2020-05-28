#pragma once

#include "engine/namespace.h"

#include "engine/core/core.h"
#include "engine/program/program.h"
#include "engine/scene/scene.h"
#include "engine/model/skeleton.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class							engine::renderer
{
	friend class				core;

private :
								renderer();
public :
	virtual						~renderer() = default;
public :

START_GLOBAL_CUSTOM_INITIALIZER(renderer)
	engine::core::connect_renderer();
FINISH_GLOBAL_CUSTOM_INITIALIZER

	static void					target(const model::instance::ptr &target)
	{
		instance()->targets.instances.push_back(target);
	}

	static void					target(const model::group::ptr &target)
	{
		instance()->targets.groups.push_back(target);
	}

	bool						request = true;

private :

IMPLEMENT_GLOBAL_INSTANCER(renderer)

	struct
	{
		using					instances_type = vector<model::instance::ptr>;
		using					groups_type = vector<model::group::ptr>;

		instances_type			instances;
		groups_type				groups;
	}							targets;

	void						render();
	void						render(const model::instance::ptr &instance);
	void						render(const model::group::ptr &group);

	void						callback();

	engine::program::program	program;
	engine::scene::scene		scene;

	using 						uniform_int = engine::program::uniform<int>;
	using 						uniform_float = engine::program::uniform<float>;
	using 						uniform_vec3 = engine::program::uniform<vec3>;
	using 						uniform_mat4 = engine::program::uniform<mat4>;

	struct						texture_wrap
	{
		uniform_int 			is_valid;
		uniform_int 			value;
	};

	struct
	{
		uniform_mat4			projection;
		uniform_mat4			view;

		struct
		{
			struct
			{
				uniform_vec3	ambient;
				uniform_vec3	diffuse;
				uniform_vec3	specular;
				uniform_vec3	emission;
				uniform_float	alpha;
			}					unite;

			struct
			{
				texture_wrap	ambient;
				texture_wrap	diffuse;
				texture_wrap	specular;
			}					textures;
		}						material;

		struct
		{
			uniform_vec3		camera;
			uniform_vec3		position;
		}						light;

		uniform_int 			does_mesh_have_bones;
		uniform_mat4 			bones_transformations[model::skeleton::bones_limit];

		struct
		{
			uniform_mat4		scaling;
			uniform_mat4		translation;
			uniform_mat4		rotation;
		}						instance;

		struct
		{
			uniform_mat4		scaling;
			uniform_mat4		translation;
			uniform_mat4		rotation;
		}						group;
	}							uniforms;
};