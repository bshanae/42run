#pragma once

#include "engine/namespace.h"

#include "engine/abstract/bitflags_wrapper.h"
#include "engine/model/bone.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class							engine::model::manager
{
public :
								manager() = default;
								~manager() = default;

START_GLOBAL_INITIALIZER(manager)
FINISH_GLOBAL_INITIALIZER

	enum class					flag : uint
	{
		triangulate = 1u << 1u,
		analyze = 1u << 2u,
		center = 1u << 3u
	};

	using						flag_wrapper = engine::abstract::bitflags_wrapper<flag>;

	static shared<model>		make(const path &source, flag_wrapper wrap = flag_wrapper());

private :

IMPLEMENT_GLOBAL_INSTANCER(manager)

	Assimp::Importer			importer;
	const aiScene				*scene = nullptr;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<unique<mesh>>		meshes;
	vector<shared<bone>>		bones;

	unique<skeleton>			skeleton;

	path						directory;

	shared<model>				make_non_static(const path &source, flag_wrapper wrap);

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