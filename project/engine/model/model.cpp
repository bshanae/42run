#include "model.h"

#include "engine/converter/converter.h"

using namespace				engine;

							model::model(const path &source)
{
	Assimp::Importer		importer;
	const auto				*scene = importer.ReadFile(source, aiProcessPreset_TargetRealtime_Fast);

	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
		throw (exception::make_object<exception::id::ASSIMP>());

	directory = source.parent_path();

	process_node(scene->mRootNode, scene);
}

void						model::process_node(aiNode *node, const aiScene *scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
		meshes.push_back(move(process_mesh(scene->mMeshes[node->mMeshes[i]], scene)));

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i], scene);
}

unique_ptr<mesh>			model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
	vector<mesh::vertex>	vertices;
	vector<unsigned>		indices;
	unique_ptr<material>	material;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh::vertex		vertex;

		vertex.position = converter::to_glm(mesh->mVertices[i]);
		vertex.normal = converter::to_glm(mesh->mNormals[i]);
		vertex.UV = mesh->mTextureCoords[0] ? converter::to_glm(mesh->mTextureCoords[0][i]) : vec2();

		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			indices.push_back(mesh->mFaces[i].mIndices[j]);

	if (mesh->mMaterialIndex >= 0)
		material = move(process_material(scene->mMaterials[mesh->mMaterialIndex]));
	else
		material = make_unique<engine::material>();

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