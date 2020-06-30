#pragma once

#include "UI/namespace.h"

class					UI::renderer : public engine::renderer
{
public :
						renderer() :
							engine::renderer(sources().vertex_shader, sources().fragment_shader)
	{
		auto			projection = glm::ortho
		(
			0.f,
			(float)engine::settings().window_size.x,
			(float)engine::settings().window_size.y,
			0.f
		);

		uniforms.texture = uniform<int>();
		uniforms.color = uniform<vec3>();
		uniforms.projection = uniform<mat4>();

		program->use(true);

		uniforms.texture.upload(0);
		uniforms.projection.upload(projection);

		program->use(false);
	}
						~renderer() = default;
private :

	void				render(const shared<engine::game_object::game_object> &object) const override
	{

	}

	struct
	{
		uniform<int>	texture;
		uniform<vec3>	color;
		uniform<mat4>	projection;
	}					uniforms;
};


