#pragma once

#include "engine/namespace.h"

#include "engine/texture/texture.h"

class					engine::mesh
{
	friend class 		renderer;
	friend class 		model;

public:

	struct				vertex
	{
		vec3			position;
		vec3			normal;
		vec2			UV;
	};

						mesh(
						vector<vertex> &vertices,
						vector<unsigned> &indices,
						vector<texture> &textures);
						~mesh() = default;
private:

	vector<vertex>		vertices;
	vector<unsigned>	indices;
	vector<texture>		textures;

	unsigned int		VAO = -1;
	unsigned int		VBO = -1;
	unsigned int		IBO = -1;
};