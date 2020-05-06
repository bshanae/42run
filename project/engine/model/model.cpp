//#include "model.h"

#include "engine/converter/converter.h"

using namespace				engine;

							model::model(const path &source)
{
	scene = importer.ReadFile(source, aiProcessPreset_TargetRealtime_Fast);

	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
		throw (exception::make_object<exception::id::ASSIMP>());

	directory = source.parent_path();

	process_node(scene->mRootNode);
	process_bones();
	process_animations();
}

#warning "Divide into process_nodes and process_meshes"
void						model::process_node(aiNode *node)
{
	nodes.push_back(node);

	for (int i = 0; i < node->mNumMeshes; i++)
		meshes.push_back(move(process_mesh(scene->mMeshes[node->mMeshes[i]])));

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i]);
}

unique_ptr<mesh>			model::process_mesh(aiMesh *mesh)
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
		material = make_unique<engine::material>();

//							BONES

#warning "Range based loop"
	for (int i = 0; i < mesh->mNumBones; i++)
	{
		aiBone*				bone = mesh->mBones[i];

		for (int j = 0; j < bone->mNumWeights; j++)
		{
			aiVertexWeight	vertexWeight = bone->mWeights[j];
			int				startVertexID = vertexWeight.mVertexId;

			for (int k = 0; k < mesh::number_of_bones; k++)
			{
				if (vertices[startVertexID].bones[k].weight == 0.0)
				{
					vertices[startVertexID].bones[k].id = find_bone(converter::to_string(bone->mName)).second;
					vertices[startVertexID].bones[k].weight = vertexWeight.mWeight;

					break ;
				}

				if (k == mesh::number_of_bones - 1)
				{
					cout << "ERROR::LOADING MORE THAN " << mesh::number_of_bones << " BONES\n"; //this could take a lot of time
					break;
				}
			}
		}
	}

	return (make_unique<engine::mesh>(vertices, indices, material));
}

unique_ptr<material>	model::process_material(aiMaterial *source)
{
	auto				target = make_unique<material>();

	aiColor3D			ambient;
	aiColor3D			diffuse;
	aiColor3D			specular;

	source->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	source->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	source->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	target->colors.ambient = converter::to_glm(ambient);
	target->colors.diffuse = converter::to_glm(diffuse);
	target->colors.specular = converter::to_glm(specular);

	auto				emplace_texture = [this, source](optional<texture> &target, aiTextureType type)
	{
		aiString		file;

		if (source->GetTextureCount(type) == 0)
			return ;

		source->GetTexture(type, 0, &file);
		target.emplace(directory / converter::to_path(file));
	};

	emplace_texture(target->textures.diffuse, aiTextureType_DIFFUSE);
	emplace_texture(target->textures.specular, aiTextureType_SPECULAR);

	return (target);
}