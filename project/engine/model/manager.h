#pragma once

#include "engine/namespace.h"

#include "engine/abstract/global.h"
#include "engine/model/bone.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"

class							engine::model::manager
{
	friend class 				renderer;

private :
								manager() = default;
public :
								~manager() = default;

IMPLEMENT_GLOBAL_INITIALIZER(manager)

	static model::ptr			make_model(const path &source);
	static instance::ptr		make_instance(model::ptr model)
	{
		return (instance::make_ptr(model));
	}

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<mesh::ptr>			meshes;
	vector<bone::ptr>			bones;

	skeleton::ptr				skeleton;

	path						directory;

	model::ptr					make_model_non_static(const path &source);

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