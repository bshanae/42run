#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/core/core.h"
#include "engine/program/program.h"
#include "engine/scene/scene.h"
#include "engine/model/skeleton.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"

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

	static void					add_target(const model::instance::ptr &model)
	{
		instance()->models.push_back(model);
	}

	bool						request = true;

private :

IMPLEMENT_GLOBAL_INSTANCER(renderer)

	using						models_type = vector<shared_ptr<model::instance>>;
	models_type					models;

	void						render();
	void						render(const model::instance::ptr &model);

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
	}							uniforms;
};