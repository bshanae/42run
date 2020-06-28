#pragma once

#include "game/namespace.h"

class								game::renderer : public engine::renderer
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

	void							render(const shared<model::instance> &instance) const;
	void							render(const shared<model::group> &group) const;

	void							callback();

	static constexpr float			scene_check_frequency = 1.f / 30.f;

	interface::timer				check_scene_timer;

	interface::callback				press_callback;
	interface::callback				hold_callback;

	struct							texture
	{
		uniform_int 				is_valid;
		uniform_int 				value;
	};
	
	struct 							light
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
				texture				ambient;
				texture				diffuse;
				texture				specular;
			}						textures;
		}							material;
		
		struct
		{
			uniform_vec3			camera_position;

			uniform_int				lights_size;
			light					lights[SHARED_LIGHTS_CAPACITY];
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