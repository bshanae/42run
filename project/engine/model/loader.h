#pragma once

#include "engine/namespace.h"

#include "engine/abstract/bitflag_wrapper.h"
#include "engine/model/bone.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class							engine::model::loader
{
	friend class				engine::model::model;

public :
								loader() = default;
								~loader() = default;
private :

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<unique<mesh>>		meshes;
	vector<shared<bone>>		bones;

	void						load(model &model, const string &source, flag_wrapper wrap);

	void						load_nodes();
	void						load_meshes();
	void						load_bones();
	void						load_animations();

	unique<mesh>				process_mesh(aiMesh *mesh);
	unique<material>			process_material(aiMaterial *material);
	void						process_node(aiNode *node);

	aiNode						*find_node(const string &name);
	pair<shared<bone>, int>		find_bone(const string &name);
	aiNodeAnim					*find_animation(const string &name);
};