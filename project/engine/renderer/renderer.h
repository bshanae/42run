#pragma once

#include "engine/namespace.h"

#include "engine/camera/camera.h"
#include "engine/program/program.h"
#include "engine/model/model.h"

class						engine::renderer
{
	friend class			core;

public :
							renderer() :
							program("project/resources/vertex.glsl", "project/resources/fragment.glsl")
	{
		uniforms.projection.emplace(program.find_uniform_location("uniform_projection"));
		uniforms.view.emplace(program.find_uniform_location("uniform_view"));
		//uniforms.texture.emplace(program.find_uniform_location("uniform_texture"));
	}
	virtual					~renderer() = default;

protected :

	virtual void			render() = 0;

	void					render(const model &model)
	{
		for (auto &mesh : model.meshes)
		{
			unsigned int	diffuse_index = 1;
			unsigned int	specular_index = 1;

			for(unsigned int i = 0; i < mesh.textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				uniforms.texture->save(i);
				glBindTexture(GL_TEXTURE_2D, mesh.textures[i].object);
			}
			glActiveTexture(GL_TEXTURE0);

			glBindVertexArray(mesh.VAO);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	engine::program		program;

private :

	using 				uniform_mat4 = optional<uniform<mat4>>;
	using 				uniform_int = optional<uniform<int>>;

protected :

	struct
	{
		uniform_mat4	projection;
		uniform_mat4	view;
		uniform_int		texture;
	}					uniforms;

	engine::camera		camera;
};