#pragma once

#include "engine/namespace.h"

#include "engine/model/mesh.h"

class							engine::model
{
	friend class 				renderer;

public:

	explicit					model(const path &source);
								~model() = default;

private:

	vector<unique_ptr<mesh>>	meshes;
	path						directory;

	void						process_node(aiNode *node, const aiScene *scene);
	unique_ptr<mesh>			process_mesh(aiMesh *mesh, const aiScene *scene);
	unique_ptr<material>		process_material(aiMaterial *material);
};

