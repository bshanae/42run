#include "loader.h"

#include "engine/converter/converter.h"
#include "engine/model/material.h"
#include "engine/model/mesh.h"

using namespace					engine;

void							model::loader::load(model &model, const path &source, flag_wrapper flags)
{
	uint 						assimp_flags = 0;

	if (flags & flag::triangulate)
		assimp_flags |= aiProcess_Triangulate;

	importer.ReadFile(source, assimp_flags);

	scene = importer.GetOrphanedScene();

#if DEBUG_VERBOSE
	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
	{
		cout << "DEBUG // ASSIMP OUTPUT" << endl;
		cout << importer.GetErrorString() << endl;
		error::raise(error::id::ASSIMP_error);
	}
#else
	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
		error::raise(error::id::ASSIMP_error);
#endif

	nodes.clear();
	animations.clear();

	meshes.clear();
	bones.clear();

	directory = source.parent_path();

	load_nodes();
	load_animations();
	load_bones();
	load_meshes();

	model.meshes.clear();

	model.assimp_scene = shared_ptr<const aiScene>(scene);
	model.meshes = move(meshes);
	model.skeleton = make_unique<engine::model::skeleton>(bones);

	if (flags & flag::analyze or flags & flag::center)
		model.analyze();
	if (flags & flag::center)
		model.center();
}


// /////////////////////////////////////////////////////////////////////////////
//								LOAD_X
// /////////////////////////////////////////////////////////////////////////////


void							model::loader::load_nodes()
{
	process_node(scene->mRootNode);
}

void							model::loader::load_meshes()
{
	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(process_mesh(scene->mMeshes[i]));
}

void							model::loader::load_bones()
{
	shared<bone>				pointer;

	for (int i = 0; i < scene->mNumMeshes; i++)
		for (int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
		{
			string				name = scene->mMeshes[i]->mBones[j]->mName.data;
			mat4				offset = converter::to_glm(scene->mMeshes[i]->mBones[j]->mOffsetMatrix);

			pointer = make_shared<engine::model::bone>(bones.size(), name, offset);

			pointer->node = find_node(name);
			pointer->animation = find_animation(name);

			if (not pointer->animation)
				warning::raise(warning::id::model_animation_not_found);

			bones.push_back(move(pointer));

		}

	for (auto &bone : bones)
	{
		auto					parent_name = converter::to_string(bone->node->mParent->mName);
		auto					parent_bone = find_bone(parent_name).first;

		bone->parent = parent_bone;
	}
}

void							model::loader::load_animations()
{
	if (scene->mNumAnimations == 0)
		return;

	for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
		animations.push_back(scene->mAnimations[0]->mChannels[i]);
}


// /////////////////////////////////////////////////////////////////////////////
//								PROCESS_X
// /////////////////////////////////////////////////////////////////////////////


void							model::loader::process_node(aiNode *node)
{
	nodes.push_back(node);

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i]);
}

unique<model::mesh>				model::loader::process_mesh(aiMesh *mesh)
{
	vector<vertex>				vertices;
	vector<unsigned>			indices;
	unique<material>			material;

//								VERTICES

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		class vertex			vertex;

		vertex.position = converter::to_glm(mesh->mVertices[i]);
		vertex.normal = converter::to_glm(mesh->mNormals[i]);
		vertex.UV = mesh->mTextureCoords[0] ? converter::to_glm(mesh->mTextureCoords[0][i]) : vec2();

		vertices.push_back(vertex);
	}

//								FACES

	for (int i = 0; i < mesh->mNumFaces; i++)
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			indices.push_back(mesh->mFaces[i].mIndices[j]);

//								MATERIAL

	if (mesh->mMaterialIndex >= 0)
		material = process_material(scene->mMaterials[mesh->mMaterialIndex]);
	else
		material = make_unique<engine::model::material>();

//								BONES

	aiBone*						bone;
	aiVertexWeight				weight;
	int							id;

	for (int i = 0; i < mesh->mNumBones; i++)
	{
		bone = mesh->mBones[i];

		for (int j = 0; j < bone->mNumWeights; j++)
		{
			weight = bone->mWeights[j];
			id = (int)weight.mVertexId;

			for (int k = 0; k < vertex::bones_limit; k++)
			{
				if (vertices[id].bones_weights[k] == 0.0f)
				{
					vertices[id].bones_ids[k] = find_bone(converter::to_string(bone->mName)).second;
					vertices[id].bones_weights[k] = weight.mWeight;

					break ;
				}

				if (k == vertex::bones_limit - 1)
					error::raise(error::id::model_too_many_bones);
			}
		}
	}

	return (make_unique<engine::model::mesh>(vertices, indices, material));
}

unique<model::material>			model::loader::process_material(aiMaterial *source)
{
	auto						target = make_unique<engine::model::material>();

	aiColor3D					ambient;
	aiColor3D					diffuse;
	aiColor3D					specular;
	aiColor3D					emission;
	float						opacity;

#define GET_MATERIAL_PROPERTY(key, target)										\
	if (source->Get(key, target) != AI_SUCCESS)									\
		warning::raise(warning::id::model_animation_not_found);

	GET_MATERIAL_PROPERTY(AI_MATKEY_COLOR_AMBIENT, ambient);
	GET_MATERIAL_PROPERTY(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	GET_MATERIAL_PROPERTY(AI_MATKEY_COLOR_SPECULAR, specular);
	GET_MATERIAL_PROPERTY(AI_MATKEY_COLOR_EMISSIVE, emission);
	GET_MATERIAL_PROPERTY(AI_MATKEY_OPACITY, opacity);

	target->unite.ambient = converter::to_glm(ambient);
	target->unite.diffuse = converter::to_glm(diffuse);
	target->unite.specular = converter::to_glm(specular);
	target->unite.emission = converter::to_glm(emission);
	target->unite.alpha = opacity;

	auto						construct_texture = [this, source](unique<texture> &target, aiTextureType type)
	{
		aiString				file;

		if (source->GetTextureCount(type) == 0)
			return ;

		source->GetTexture(type, 0, &file);
		target = make_unique<engine::model::texture>(directory / converter::to_path(file));
	};

	construct_texture(target->textures.ambient, aiTextureType_AMBIENT);
	construct_texture(target->textures.diffuse, aiTextureType_DIFFUSE);
	construct_texture(target->textures.specular, aiTextureType_SPECULAR);

	return (target);
}


// /////////////////////////////////////////////////////////////////////////////
//								FIND_X
// /////////////////////////////////////////////////////////////////////////////


aiNode							*model::loader::find_node(const string &name)
{
	for (const auto &node : nodes)
		if (node->mName.data == name)
			return (node);

	return (nullptr);
}

pair<shared<model::bone>, int>	model::loader::find_bone(const string &name)
{
	for (const auto &bone : bones)
		if (bone->name == name)
			return {bone, bone->id};

	warning::raise(warning::id::model_bone_not_found);

#if DEBUG_VERBOSE
	if (not warning::is_muted)
		cout << "Name = " << name << endl;
#endif

	return {shared<bone>(), -1};
}

aiNodeAnim						*model::loader::find_animation(const string &name)
{
	for (const auto &animation : animations)
		if (animation->mNodeName.data == name)
			return (animation);

	warning::raise(warning::id::model_animation_not_found);
	return (nullptr);
}
