#pragma once

#include "engine/namespace.h"

#include "engine/abstract/pointer.h"
#include "engine/model/material.h"

class							engine::model::mesh
{
private :

	friend class 				model;
	friend class 				manager;
	friend class 				engine::renderer;

public :

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(mesh)

	struct						vertex
	{
		vec3					position;
		vec3					normal;
		vec2					UV;

		static constexpr int	bones_limit = 6;

		float					bones_ids[bones_limit] = {0.0f};
		float					bones_weights[bones_limit] = {0.0f};
	};

								mesh(
								vector<vertex> &vertices,
								vector<unsigned> &indices,
								material::ptr &material);
								~mesh();
private:

	vector<vertex>				vertices;
	vector<unsigned>			indices;
	material::ptr				material;

	unsigned int				VAO = -1;
	unsigned int				VBO = -1;
	unsigned int				IBO = -1;
};