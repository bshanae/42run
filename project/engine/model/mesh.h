#pragma once

#include "engine/namespace.h"

#include "engine/model/vertex.h"
#include "engine/model/material.h"

class					engine::model::mesh
{
	friend class 		engine::model::model;
	friend class 		engine::model::loader;
	friend class 		engine::model::reader;

public :
						mesh
						(
							const vector<vertex> &vertices,
							const vector<unsigned> &indices,
							unique<material> &material
						);
						~mesh();
private:

	vector<vertex>		vertices;
	vector<unsigned>	indices;
	unique<material>	material;

	unsigned int		VAO = -1;
	unsigned int		VBO = -1;
	unsigned int		IBO = -1;
};