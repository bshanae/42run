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
	}
	virtual					~renderer() = default;

protected :

	virtual void			render() = 0;

	void					render(const model &model)
	{
		for (auto &mesh : model.meshes)
		{
			glBindVertexArray(mesh.VAO);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	engine::program		program;

private :

	using 				uniform_mat4 = optional<uniform<mat4>>;

protected :

	struct
	{
		uniform_mat4	projection;
		uniform_mat4	view;
	}					uniforms;

	engine::camera		camera;
};