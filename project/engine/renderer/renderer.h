#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/program/program.h"
#include "engine/scene/scene.h"
#include "engine/model/skeleton.h"
#include "engine/model/model.h"

class							engine::renderer
{
	friend class				core;

private :
								renderer();
public :
	virtual						~renderer() = default;
public :

IMPLEMENT_GLOBAL_INITIALIZER(renderer)

	static void					add_target(const shared_ptr<model::model> &model)
	{
		instance()->models.push_back(model);
	}

	bool						request = true;

private :

IMPLEMENT_GLOBAL_INSTANCER(renderer)

	using						models_type = vector<shared_ptr<model::model>>;
	models_type 				models;

	void						render();
	void						render(const shared_ptr<model::model> &model);

	void						callback();

	engine::program::program	program;
	engine::scene::scene		scene;

	using 						uniform_int = engine::program::uniform<int>;
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
			}					colors;

			struct
			{
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
		uniform_mat4 			bones[model::skeleton::limit_for_bones];
	}							uniforms;
};