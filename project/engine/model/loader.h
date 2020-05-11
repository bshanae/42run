#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/model/model.h"
#include "engine/model/bone.h"

class							engine::model::loader
{
	friend class 				renderer;

private :
								loader() = default;
public :
								~loader() = default;

IMPLEMENT_GLOBAL_INITIALIZER(loader)

	static model::ptr			load(const path &source);

private :

IMPLEMENT_GLOBAL_INSTANCER(loader)

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<mesh::ptr>			meshes;
	vector<bone::ptr>			bones;

	skeleton::ptr				skeleton;

	path						directory;

	model::ptr					load_non_static(const path &source);

	void						load_nodes();
	void						load_meshes();

	mesh::ptr					process_mesh(aiMesh *mesh);
	void						load_bones();
	void						load_animations();
	material::ptr				process_material(aiMaterial *material);

	void						process_node(aiNode *node);

	aiNode						*find_node(const string &name);
	pair<bone::ptr, int>		find_bone(const string &name);
	aiNodeAnim					*find_animation(const string &name);
};