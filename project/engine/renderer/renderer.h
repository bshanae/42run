#pragma once

#include "engine/namespace.h"

#include "engine/camera/camera.h"
#include "engine/program/program.h"
#include "engine/model/model.h"

class							engine::renderer
{
	friend class				core;

public :
								renderer();
	virtual						~renderer() = default;

	void						callback();

	bool						request = true;

protected :

	virtual void				render() = 0;
	void						render(const model &model);

	engine::program				program;

private :

	using 						uniform_mat4 = optional<uniform<mat4>>;
	using 						uniform_vec3 = optional<uniform<vec3>>;
	using 						uniform_int = optional<uniform<int>>;

protected :

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
			}					textures;
		}						material;
	}							uniforms;

	engine::camera				camera;
};