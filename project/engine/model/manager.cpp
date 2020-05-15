#include "manager.h"

#include "engine/converter/converter.h"
#include "engine/model/material.h"
#include "engine/model/mesh.h"

using namespace				engine;

model::model::ptr			model::manager::make_model(const path &source)
{
	auto					&instance = manager::instance();

	return (instance->make_model_non_static(source));
}

model::model::ptr			model::manager::make_model_non_static(const path &source)
{
	scene = importer.ReadFile(source, aiProcessPreset_TargetRealtime_MaxQuality);

	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
	{
		std::cout << "ASSIMP ERROR" << std::endl;
		std::cout << importer.GetErrorString() << std::endl;
		common::error::raise(common::error::id::ASSIMP_error);
	}

	nodes.clear();
	meshes.clear();

	directory = source.parent_path();

	load_nodes();
	load_animations();
	load_bones();
	load_meshes();

	skeleton = engine::model::skeleton::make_ptr(bones);

	return (model::ptr(new model(meshes, skeleton)));
}


// /////////////////////////////////////////////////////////////////////////////
//							LOAD_X
// /////////////////////////////////////////////////////////////////////////////


void						model::manager::load_nodes()
{
	process_node(scene->mRootNode);
}

void						model::manager::load_meshes()
{
	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(process_mesh(scene->mMeshes[i]));
}

void						model::manager::load_bones()
{
	bone::ptr				pointer;

	for (int i = 0; i < scene->mNumMeshes; i++)
		for (int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
		{
			string			name = scene->mMeshes[i]->mBones[j]->mName.data;
			mat4			offset = converter::to_glm(scene->mMeshes[i]->mBones[j]->mOffsetMatrix);

			pointer = engine::model::bone::make_ptr(bones.size(), name, offset);

			pointer->node = find_node(name);
			pointer->animation = find_animation(name);

			if (not pointer->animation)
				common::warning::raise(common::warning::id::model_animation_not_found);

			bones.push_back(move(pointer));

		}

	for (auto &bone : bones)
	{
		auto				parent_name = converter::to_string(bone->node->mParent->mName);
		auto				parent_bone = find_bone(parent_name).first;

		bone->parent = parent_bone;
	}
}

void						model::manager::load_animations()
{
	if (scene->mNumAnimations == 0)
		return;

	for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
		animations.push_back(scene->mAnimations[0]->mChannels[i]);
}


// /////////////////////////////////////////////////////////////////////////////
//							PROCESS_X
// /////////////////////////////////////////////////////////////////////////////


void						model::manager::process_node(aiNode *node)
{
	nodes.push_back(node);

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i]);
}

model::mesh::ptr			model::manager::process_mesh(aiMesh *mesh)
{
	vector<mesh::vertex>	vertices;
	vector<unsigned>		indices;
	material::ptr			material;

//							VERTICES

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh::vertex		vertex;

		vertex.position = converter::to_glm(mesh->mVertices[i]);
		vertex.normal = converter::to_glm(mesh->mNormals[i]);
		vertex.UV = mesh->mTextureCoords[0] ? converter::to_glm(mesh->mTextureCoords[0][i]) : vec2();

		vertices.push_back(vertex);
	}

//							FACES

	for (int i = 0; i < mesh->mNumFaces; i++)
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			indices.push_back(mesh->mFaces[i].mIndices[j]);

//							MATERIAL

	if (mesh->mMaterialIndex >= 0)
		material = move(process_material(scene->mMaterials[mesh->mMaterialIndex]));
	else
		material = engine::model::material::make_ptr();

//							BONES

	aiBone*					bone;
	aiVertexWeight			weight;
	int						id;

	for (int i = 0; i < mesh->mNumBones; i++)
	{
		bone = mesh->mBones[i];

		for (int j = 0; j < bone->mNumWeights; j++)
		{
			weight = bone->mWeights[j];
			id = (int)weight.mVertexId;

			for (int k = 0; k < mesh::vertex::bones_limit; k++)
			{
				if (vertices[id].bones_weights[k] == 0.0f)
				{
					vertices[id].bones_ids[k] = find_bone(converter::to_string(bone->mName)).second;
					vertices[id].bones_weights[k] = weight.mWeight;

					break ;
				}

				if (k == mesh::vertex::bones_limit - 1)
					common::error::raise(common::error::id::model_too_many_bones);
			}
		}
	}

	return (engine::model::mesh::make_ptr(vertices, indices, move(material)));
}

model::material::ptr		model::manager::process_material(aiMaterial *source)
{
	auto					target = engine::model::material::make_ptr();

	aiColor3D				ambient;
	aiColor3D				diffuse;
	aiColor3D				specular;

	source->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	source->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	source->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	target->colors.ambient = converter::to_glm(ambient);
	target->colors.diffuse = converter::to_glm(diffuse);
	target->colors.specular = converter::to_glm(specular);

	auto					construct_texture = [this, source](texture::ptr &target, aiTextureType type)
	{
		aiString			file;

		if (source->GetTextureCount(type) == 0)
			return ;

		source->GetTexture(type, 0, &file);
		target = engine::model::texture::make_ptr(directory / converter::to_path(file));
	};

	construct_texture(target->textures.diffuse, aiTextureType_DIFFUSE);
	construct_texture(target->textures.specular, aiTextureType_SPECULAR);

	return (target);
}


// /////////////////////////////////////////////////////////////////////////////
//							FIND_X
// /////////////////////////////////////////////////////////////////////////////


aiNode						*model::manager::find_node(const string &name)
{
	for (int i = 0; i < nodes.size(); i++)
		if (nodes[i]->mName.data == name)
			return (nodes[i]);

	return (nullptr);
}

pair<model::bone::ptr, int>	model::manager::find_bone(const string &name)
{
	for (int i = 0; i < bones.size(); i++)
		if (bones[i]->name == name)
			return {bones[i], bones[i]->id};

	if (name != "RootNode")
		common::warning::raise(common::warning::id::model_bone_not_found);
	return {bone::ptr(), -1};
}

aiNodeAnim					*model::manager::find_animation(const string &name)
{
	for (int i = 0; i < animations.size(); i++)
		if (animations[i]->mNodeName.data == name)
			return (animations[i]);

	common::warning::raise(common::warning::id::model_animation_not_found);
	return (nullptr);
}
