#pragma once

#include "engine/namespace.h"

#include "engine/model/mesh.h"

class						engine::model
{
	friend class 			renderer;

public:
	model(char *path)
	{
		loadModel(path);
	}

private:

	std::vector<mesh>		meshes;
	std::string				directory;

	void					loadModel(std::string path)
	{
		Assimp::Importer	importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
#warning "Use modern methods?"
		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);
	}

	void					processNode(aiNode *node, const aiScene *scene)
	{
		// обработать все полигональные сетки в узле(если есть)
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		// выполнить ту же обработку и для каждого потомка узла
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	mesh					processMesh(aiMesh *mesh, const aiScene *scene)
	{
		std::vector<Vertex>		vertices;
		std::vector<unsigned>	indices;

		std::vector<Texture>	textures;

		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			vertex.Position = glm::vec3(
				mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			vertex.Normal = glm::vec3(
				mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			if(mesh->mTextureCoords[0]) // сетка обладает набором текстурных координат?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for(unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// обработка материала
		if(mesh->mMaterialIndex >= 0)
		{
		}

		return (class mesh){vertices, indices, textures};
	}

	std::vector<Texture>	loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

