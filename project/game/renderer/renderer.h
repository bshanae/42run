#pragma once

#include "game/namespace.h"

#include "game/engine_extensions/reader.h"

class								game::renderer :
										public engine::renderer,
										public game::engine_extensions::reader
{
	friend class					game::manager;

public :
									renderer();
									~renderer() override = default;
private :

	void							initialize_uniforms();

	void 							upload_camera_uniforms() const;
	void 							upload_light_uniforms() const;

	void							render(const shared<game_object::game_object> &object) const override;

	void							render(const shared<model::group> &group) const;
	void							render(const shared<model::instance> &instance) const;

	void							callback();

	static constexpr float			scene_check_frequency = 1.f / 30.f;

	interface::timer				check_scene_timer;

	interface::callback				press_callback;
	interface::callback				hold_callback;

	unique<program::program>		program;

	template						<typename type>
	using							uniform = program::uniform<type>;

	struct							texture
	{
		uniform<int> 				is_valid;
		uniform<int> 				value;
	};
	
	struct 							light
	{
		uniform<int>				type;
		uniform<vec3>				parameter_a;
		uniform<vec3>				parameter_b;
		uniform<float>				parameter_c;
		uniform<float>				parameter_d;
		uniform<vec3>				color;
		uniform<float>				power;
	};

	struct
	{
		uniform<mat4>				projection;
		uniform<mat4>				view;

		struct
		{
			struct
			{
				uniform<vec3>		ambient;
				uniform<vec3>		diffuse;
				uniform<vec3>		specular;
				uniform<vec3>		emission;
				uniform<float>		alpha;
			}						unite;

			struct
			{
				texture				ambient;
				texture				diffuse;
				texture				specular;
			}						textures;
		}							material;
		
		struct
		{
			uniform<vec3>			camera_position;

			uniform<int>			lights_size;
			light					lights[SHARED_LIGHTS_CAPACITY];
		}							scene;

		uniform<int> 				does_mesh_have_bones;
		uniform<mat4> 				bones_transformations[model::skeleton::bones_limit];

		struct
		{
			uniform<mat4>			scaling;
			uniform<mat4>			translation;
			uniform<mat4>			rotation;
		}							instance;

		struct
		{
			uniform<mat4>			scaling;
			uniform<mat4>			translation;
			uniform<mat4>			rotation;
		}							group;

		struct
		{
			uniform<int>			use;
			uniform<float>			factor;
			uniform<vec4>			color;
		}							color_mix;

		struct
		{
			uniform<float>			density;
			uniform<float>			gradient;
			uniform<int>			use;
			uniform<vec3>			background;
		}							fog;
	}								uniforms;
};