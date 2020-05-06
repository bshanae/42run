#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"

class							engine::model::loader
{
	friend class 				renderer;

public:
								loader() = default;
								~loader() = default;

	model						make(const path &source);

private:

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<unique_ptr<mesh>>	meshes;
	vector<bone *>				bones;

	path						directory;

	void						load_nodes();
	void						load_meshes();

	unique_ptr<mesh>			process_mesh(aiMesh *mesh);
	void						load_bones();
	void						load_animations();
	unique_ptr<material>		process_material(aiMaterial *material);

	void						process_node(aiNode *node);

	aiNode						*find_node(const string &name);
	pair<bone *, int>			find_bone(const string &name);
	aiNodeAnim					*find_animation(const string &name);
};