#pragma once

#include "engine/namespace.h"

#include "engine/model/mesh.h"

class						engine::model
{
	friend class 			renderer;

public:

							model(const path &source);
							~model() = default;

private:

	vector<mesh>			meshes;
	path					directory;

	void					process_node(aiNode *node, const aiScene *scene);
	mesh					process_mesh(aiMesh *mesh, const aiScene *scene);

	vector<mesh::texture>	loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

