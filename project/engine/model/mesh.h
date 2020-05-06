#pragma once

#include "engine/namespace.h"

class						engine::model::mesh
{
private :

	friend class 			model;
	friend class 			loader;
	friend class 			engine::renderer;

	static constexpr int	number_of_bones = 6;

public:


	struct					bone
	{
		float				id = 0.f;
		float				weight = 0.f;
	};

	struct					vertex
	{
		vec3				position;
		vec3				normal;
		vec2				UV;
		bone				bones[number_of_bones];
	};

							mesh(
							vector<vertex> &vertices,
							vector<unsigned> &indices,
							unique_ptr<material> &material);
#warning "Create destructor"
							~mesh() = default;
private:

	vector<vertex>			vertices;
	vector<unsigned>		indices;
	unique_ptr<material>	material;

	unsigned int			VAO = -1;
	unsigned int			VBO = -1;
	unsigned int			IBO = -1;
};