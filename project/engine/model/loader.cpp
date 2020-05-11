#include "loader.h"

#include "engine/converter/converter.h"
#include "engine/model/bone.h"
#include "engine/model/material.h"
#include "engine/model/mesh.h"

using namespace				engine;

shared_ptr<model::model>	model::loader::load(const path &source)
{
	auto					&instance = loader::instance();

	return (instance->load_non_static(source));
}

shared_ptr<model::model>	model::loader::load_non_static(const path &source)
{
	scene = importer.ReadFile(source, aiProcessPreset_TargetRealtime_MaxQuality);

	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
	{
		std::cout << "ASSIMP ERROR" << std::endl;
		std::cout << importer.GetErrorString() << std::endl;
		throw (exception::exception<exception::id::ASSIMP_error>());
	}

	nodes.clear();
	meshes.clear();

	directory = source.parent_path();

	load_nodes();
	load_animations();
	load_bones();
	load_meshes();

	skeleton = make_unique<engine::model::skeleton>(bones);

	return (shared_ptr<model>(new model(meshes, skeleton)));
}


// /////////////////////////////////////////////////////////////////////////////
//							LOAD_X
// /////////////////////////////////////////////////////////////////////////////


void						model::loader::load_nodes()
{
	process_node(scene->mRootNode);
}

void						model::loader::load_meshes()
{
	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(process_mesh(scene->mMeshes[i]));
}

void						model::loader::load_bones()
{

#warning "Range based loop"
	for (int i = 0; i < scene->mNumMeshes; i++)
		for (int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
		{
			string			name = scene->mMeshes[i]->mBones[j]->mName.data;
			mat4			offset = converter::to_glm(scene->mMeshes[i]->mBones[j]->mOffsetMatrix);

#warning "Unique ptr"
			bone*			bone = new engine::model::bone(bones.size(), name, offset);

			bone->node = find_node(name);
			bone->animation = find_animation(name);

#warning "Do I need this?"
			if (not bone->animation)
			{
				std::cout << "ERROR::NO ANIMATIONS FOUND FOR " << name << std::endl;
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
			std::cout << "NO PARENT BONE FOR " << bones[i]->name << std::endl;
		}
	}

	std::cerr << "Number of bones = " << bones.size() << std::endl;
}

void						model::loader::load_animations()
{
	if (scene->mNumAnimations == 0)
		return;

#warning "Range based loop?"
	for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
		animations.push_back(scene->mAnimations[0]->mChannels[i]);
}


// /////////////////////////////////////////////////////////////////////////////
//							PROCESS_X
// /////////////////////////////////////////////////////////////////////////////


void						model::loader::process_node(aiNode *node)
{
	nodes.push_back(node);

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i]);
}

unique_ptr<model::mesh>		model::loader::process_mesh(aiMesh *mesh)
{
	vector<mesh::vertex>	vertices;
	vector<unsigned>		indices;
	unique_ptr<material>	material;

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
		material = make_unique<engine::model::material>();

//							BONES

#warning "Range based loop"
	for (int i = 0; i < mesh->mNumBones; i++)
	{
		aiBone*				bone = mesh->mBones[i];

		for (int j = 0; j < bone->mNumWeights; j++)
		{
			aiVertexWeight	vertexWeight = bone->mWeights[j];
			int				startVertexID = vertexWeight.mVertexId;

			for (int k = 0; k < mesh::vertex::bones_limit; k++)
			{
				if (vertices[startVertexID].weights[k] == 0.0)
				{
					vertices[startVertexID].boneIDs[k] = find_bone(converter::to_string(bone->mName)).second;
					vertices[startVertexID].weights[k] = vertexWeight.mWeight;

					break ;
				}

				if (k == mesh::vertex::bones_limit - 1)
				{
					std::cout << "ERROR : LOADING MORE THAN " << mesh::vertex::bones_limit << " BONES\n"; //this could take a lot of time
					break;
				}
			}
		}
	}

	return (make_unique<engine::model::mesh>(vertices, indices, material));
}

unique_ptr<model::material>	model::loader::process_material(aiMaterial *source)
{
	auto					target = make_unique<engine::model::material>();

	aiColor3D				ambient;
	aiColor3D				diffuse;
	aiColor3D				specular;

	source->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	source->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	source->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	target->colors.ambient = converter::to_glm(ambient);
	target->colors.diffuse = converter::to_glm(diffuse);
	target->colors.specular = converter::to_glm(specular);

	auto					emplace_texture = [this, source](optional<texture> &target, aiTextureType type)
	{
		aiString			file;

		if (source->GetTextureCount(type) == 0)
			return ;

		source->GetTexture(type, 0, &file);
		target.emplace(directory / converter::to_path(file));
	};

	emplace_texture(target->textures.diffuse, aiTextureType_DIFFUSE);
	emplace_texture(target->textures.specular, aiTextureType_SPECULAR);

	return (target);
}


// /////////////////////////////////////////////////////////////////////////////
//							FIND_X
// /////////////////////////////////////////////////////////////////////////////


aiNode						*model::loader::find_node(const string &name)
{
	for (int i = 0; i < nodes.size(); i++)
		if (nodes[i]->mName.data == name)
			return (nodes[i]);

	return (nullptr);
}

pair<model::bone *, int>	model::loader::find_bone(const string &name)
{
	for (int i = 0; i < bones.size(); i++)
		if (bones[i]->name == name)
			return {bones[i], bones[i]->id};

	std::cerr << "42run Warning : Bone not found, name = {" << name << "}" << std::endl;
	return {nullptr, -1};
}

aiNodeAnim					*model::loader::find_animation(const string &name)
{
	for (int i = 0; i < animations.size(); i++)
		if (animations[i]->mNodeName.data == name)
			return (animations[i]);

	std::cerr << "42run Warning : Animation not found, name = {" << name << "}" << std::endl;
	return (nullptr);
}
