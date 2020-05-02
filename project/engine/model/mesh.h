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

class						engine::mesh
{
	friend class 			renderer;
	friend class 			model;

public:
							mesh(
							std::vector<Vertex> vertices,
							std::vector<unsigned int> indices,
							std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}
							~mesh() = default;

	std::vector<Vertex>		vertices;
	std::vector<unsigned>	indices;
	std::vector<Texture>	textures;
private:

	unsigned int			VAO = -1;
	unsigned int			VBO = -1;
	unsigned int			EBO = -1;
};