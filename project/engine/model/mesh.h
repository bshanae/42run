#pragma once

#include "engine/namespace.h"

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

	struct				texture
	{
		unsigned		id;
		string			type;
	};
						mesh(
						vector<vertex> vertices,
						vector<unsigned> indices,
						vector<texture> textures);
						~mesh() = default;

	vector<vertex>		vertices;
	vector<unsigned>	indices;
	vector<texture>		textures;

private:

	unsigned int		VAO = -1;
	unsigned int		VBO = -1;
	unsigned int		EBO = -1;
};