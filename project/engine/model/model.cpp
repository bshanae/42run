#include "model.h"

using namespace				engine;

							model::model(const path &source)
{
	Assimp::Importer		importer;
	const auto				*scene = importer.ReadFile(source, aiProcessPreset_TargetRealtime_MaxQuality);

	if (not scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or not scene->mRootNode)
		throw (exception::make_object<exception::id::ASSIMP>());

	directory = source.parent_path();

	process_node(scene->mRootNode, scene);
}

void						model::process_node(aiNode *node, const aiScene *scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
		meshes.push_back(process_mesh(scene->mMeshes[node->mMeshes[i]], scene));

	for (int i = 0; i < node->mNumChildren; i++)
		process_node(node->mChildren[i], scene);
}

mesh						model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
	vector<mesh::vertex>	vertices;
	vector<unsigned>		indices;
	vector<mesh::texture>	textures;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh::vertex		vertex;

		vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if(mesh->mTextureCoords[0])
			vertex.UV = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.UV = vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace				&face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return (engine::mesh(vertices, indices, textures));
}