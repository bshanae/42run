#pragma once

#include "engine/namespace.h"

#include "engine/model/material.h"

class							engine::model::mesh
{
private :

	friend class 				engine::model::model;
	friend class 				engine::model::manager;
	friend class 				engine::model::reader;

public :

	struct						vertex
	{
		vec3					position;
		vec3					normal;
		vec2					UV;

		static constexpr int	bones_limit = SHARED_BONES_IN_VERTEX;

		float					bones_ids[bones_limit] = {0.0f};
		float					bones_weights[bones_limit] = {0.0f};
	};

								mesh
								(
									vector<vertex> &vertices,
									vector<unsigned> &indices,
									unique<material> &material
								);
								~mesh();
private:

	vector<vertex>				vertices;
	vector<unsigned>			indices;
	unique<material>			material;

	unsigned int				VAO = -1;
	unsigned int				VBO = -1;
	unsigned int				IBO = -1;
};