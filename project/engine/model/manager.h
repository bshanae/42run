#pragma once

#include "engine/namespace.h"

#include "engine/abstract/enum_wrap.h"
#include "engine/model/bone.h"
#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class							engine::model::manager
{
	friend class 				renderer;

private :
								manager() = default;
public :
								~manager() = default;

IMPLEMENT_GLOBAL_INITIALIZER(manager)

	enum class					flags : uint
	{
		triangulate = 1u << 1u,
		analyze = 1u << 2u,
		center = 1u << 3u
	};

	using						flags_wrap = engine::abstract::enum_wrap<flags>;

	static model::ptr			make_model(const path &source, flags_wrap wrap = flags_wrap());

	template					<typename ...args_type>
	static instance::ptr		make_instance(args_type ...args)
	{
		return (instance::make_ptr(args...));
	}

	static group::ptr			make_group(const initializer_list<instance::ptr> &list)
	{
		return (group::make_ptr(list));
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

	model::ptr					make_model_non_static(const path &source, flags_wrap wrap);

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