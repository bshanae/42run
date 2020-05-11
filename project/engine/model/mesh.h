#pragma once

#include "engine/namespace.h"

class						engine::model::mesh
{
private :

	friend class 			model;
	friend class 			loader;
	friend class 			engine::renderer;


public :

	struct					bone
	{
		float				id = 0.f;
		float				weight = 0.f;
	};

	struct					vertex
	{
		static constexpr int	bones_limit = 6;

		vec3				position;
		vec3				normal;
		vec2				UV;
#warning "Use struct bone"
//		bone				bones[number_of_bones];

		float				boneIDs[bones_limit] = {0.0f};
		float				weights[bones_limit] = {0.0f};
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