#pragma once

#include "engine/namespace.h"

#include "engine/model/mesh.h"
#include "engine/converter/converter.h"
#include "engine/animation/bone.h"
#include "engine/animation/animation.h"
#include "engine/animation/skeleton.h"

class							engine::loader
{
	friend class 				renderer;

public:

	explicit					loader(const path &source);
	~loader() = default;
private:

	Assimp::Importer			importer;
	const aiScene				*scene;

	vector<aiNode *>			nodes;
	vector<aiNodeAnim *>		animations;

	vector<unique_ptr<mesh>>	meshes;
	vector<bone *>				bones;

	path						directory;

	void						process_node(aiNode *node);
	unique_ptr<mesh>			process_mesh(aiMesh *mesh);
	unique_ptr<material>		process_material(aiMaterial *material);

	void						process_bones()
	{

#warning "Range based loop"
		for (int i = 0; i < scene->mNumMeshes; i++)
			for (int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
			{
				string			name = scene->mMeshes[i]->mBones[j]->mName.data;
				mat4			offset = converter::to_glm(scene->mMeshes[i]->mBones[j]->mOffsetMatrix);

#warning "Unique ptr"
				bone*			bone = new class bone(bones.size(), name, offset);

				bone->node = find_node(name);
				bone->animation = find_animation(name);

#warning "Do I need this?"
				if (not bone->animation)
				{
					cout << "ERROR::NO ANIMATIONS FOUND FOR " << name << endl;
				}

				bones.push_back(bone);
			}

#warning "Range based loop"
		for (int i = 0; i < bones.size(); i++)
		{
			string				parent_name = converter::to_string(bones[i]->node->mParent->mName);
			bone*				parent_bone = find_bone(parent_name).first;

			bones[i]->parent = parent_bone; //set the parent bone for the bone

			if (not parent_bone) //if there is no parent bone
			{
				cout << "NO PARENT BONE FOR " << bones[i]->name << endl;
			}
		}

	}

	void						process_animations()
	{
		if (scene->mNumAnimations == 0)
			return;

#warning "Range based loop?"
		for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
			animations.push_back(scene->mAnimations[0]->mChannels[i]);
	}

	aiNode						*find_node(const string &name)
	{
		for (int i = 0; i < nodes.size(); i++)
			if (nodes[i]->mName.data == name)
				return (nodes[i]);

		return (nullptr);
	}

	pair<bone *, int>			find_bone(const string &name)
	{
		for (int i = 0; i < bones.size(); i++)
			if (bones[i]->name == name)
				return {bones[i], bones[i]->id};

		return {nullptr, -1};
	}

	aiNodeAnim					*find_animation(const string &name)
	{
		for (int i = 0; i < animations.size(); i++)
			if (animations[i]->mNodeName.data == name)
				return (animations[i]);

		return (0);
	}
};