#pragma once

#include "engine/namespace.h"

struct Vertex
{
	glm::vec3		Position;
	glm::vec3		Normal;
	glm::vec2		TexCoords;
};

struct Texture
{
	unsigned int	id;
	std::string		type;

};

class						mesh
{
public:
							mesh(
							std::vector<Vertex> vertices,
							std::vector<unsigned int> indices,
							std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}
							~mesh() = default;

	void					Draw(engine::program &program)
	{
#if 0
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for(unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // активируем текстурный блок, до привязки
			// получаем номер текстуры
			std::stringstream ss;
			std::string number;
			std::string name = textures[i].type;
			if(name == "texture_diffuse")
				ss << diffuseNr++; // передаем unsigned int в stream
			else if(name == "texture_specular")
				ss << specularNr++; // передаем unsigned int в stream
			number = ss.str();

			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);
#endif

		// отрисовывем полигональную сетку
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	std::vector<Vertex>		vertices;
	std::vector<unsigned>	indices;
	std::vector<Texture>	textures;
private:

	unsigned int			VAO,
							VBO,
							EBO;

	void					setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

#warning "Use .data()"
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
#warning "Use .data()"
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}
};

class						model
{
public:
							model(char *path)
		{
			loadModel(path);
		}
	void					Draw(engine::program &program)
	{
		for(unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(program);
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