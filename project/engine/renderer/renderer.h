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
		program = program::program::make_ptr
		(
			settings().glsl_path / "main.vertex.glsl",
			settings().glsl_path / "main.fragment.glsl"
		);

		initialize_data();
	}

public :
	virtual							~renderer() = default;

START_GLOBAL_CUSTOM_INITIALIZER(renderer)
	instance(false) = shared_ptr<renderer>(new renderer());
	connect_with_global();
FINISH_GLOBAL_CUSTOM_INITIALIZER

private :

IMPLEMENT_GLOBAL_INSTANCER(renderer)

	static void						connect_with_global();

	void							initialize_data();

	void 							upload_camera_data();
	void 							upload_light_data();

	void							render();
	void							render(const model::instance::ptr &instance);
	void							render(const model::group::ptr &group);

	void							animate();

	void							callback();

	interface::callback				on_press;
	interface::callback				on_hold;

	program::program::ptr			program;

	using 							uniform_int = program::uniform<int>;
	using 							uniform_float = program::uniform<float>;
	using 							uniform_vec3 = program::uniform<vec3>;
	using 							uniform_vec4 = program::uniform<vec4>;
	using 							uniform_mat4 = program::uniform<mat4>;

	struct							texture_glsl
	{
		uniform_int 				is_valid;
		uniform_int 				value;
	};
	
	struct 							light_glsl
	{
		uniform_int					type;
		uniform_vec3				parameter_a;
		uniform_vec3				parameter_b;
		uniform_float				parameter_c;
		uniform_float				parameter_d;
		uniform_vec3				color;
		uniform_float				power;
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
				texture_glsl		ambient;
				texture_glsl		diffuse;
				texture_glsl		specular;
			}						textures;
		}							material;
		
		struct
		{
			uniform_vec3			camera_position;

			uniform_int				lights_size;
			light_glsl				lights[SHARED_LIGHTS_CAPACITY];
		}							scene;

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