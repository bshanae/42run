#pragma once

#include "engine/namespace.h"

#include "engine/model/mesh.h"
#include "engine/texture/texture.h"

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

	vector<texture>			process_material(aiMaterial *material, aiTextureType purpose)
	{
		vector<texture>		textures;
		aiString			file;

		purpose = aiTextureType_DIFFUSE;

		for (int i = 0; i < material->GetTextureCount(purpose); i++)
		{
			material->GetTexture(purpose, i, &file);
			textures.emplace_back(directory / path(file.C_Str()));
		}
		return (textures);
	}
};

