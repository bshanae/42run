#include "mesh.h"

using namespace		engine;

					model::mesh::mesh
					(
						vector<vertex> &vertices,
						vector<unsigned> &indices,
						unique<engine::model::material> &material
					) :
						vertices(move(vertices)),
						indices(move(indices)),
						material(move(material))
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vertex), this->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, UV));

	for (int i = 0; i < vertex::bones_limit; i++)
	{
		glEnableVertexAttribArray(3 + i);
		glVertexAttribPointer(3 + i, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, bones_ids) + sizeof(float) * i));
	}

	for (int i = 0; i < vertex::bones_limit; i++)
	{
		glEnableVertexAttribArray(3 + vertex::bones_limit + i);
		glVertexAttribPointer(3 + vertex::bones_limit + i, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(offsetof(vertex, bones_weights) + sizeof(float) * i));
	}

	glBindVertexArray(0);
}

					model::mesh::~mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}