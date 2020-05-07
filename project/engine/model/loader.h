#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/model/model.h"

class							engine::model::loader
{
	friend class 				renderer;

private :
								loader() = default;
public :
								~loader() = default;

IMPLEMENT_GLOBAL_INITIALIZER(loader)

	static shared_ptr<model>	load(const path &source);

private :

IMPLEMENT_GLOBAL_INSTANCER(loader)

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<unique_ptr<mesh>>	meshes;
	vector<bone *>				bones;

	unique_ptr<skeleton>		skeleton;

	path						directory;

	shared_ptr<model>			load_non_static(const path &source);

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