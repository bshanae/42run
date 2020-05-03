#pragma once

#include "engine/namespace.h"

#include "engine/program/program.h"
#include "engine/model/model.h"
#include "engine/scene/scene.h"

class							engine::renderer
{
	friend class				core;

public :
								renderer();
	virtual						~renderer() = default;

	void						callback();

	bool						request = true;

	virtual void				render() = 0;

protected :

	void						render(initializer_list<const reference_wrapper<model>> models);

private :

	void						render_model(const model &model);

	engine::program				program;

private :

	using 						uniform_mat4 = optional<uniform<mat4>>;
	using 						uniform_vec3 = optional<uniform<vec3>>;
	using 						uniform_int = optional<uniform<int>>;

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
	}							uniforms;

	engine::scene				scene;
};