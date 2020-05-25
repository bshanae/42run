#include "model.h"

#include <limits>

using namespace		engine;

void				model::model::analyze()
{
	min = vec3(+1.f * std::numeric_limits<float>::infinity());
	max = vec3(-1.f * std::numeric_limits<float>::infinity());

	for (const auto &mesh : meshes)
		for (const auto &vertex : mesh->vertices)
		{
			min = glm::min(min, vertex.position);
			max = glm::max(max, vertex.position);
		}

	size = max - min;
	is_analyzed = true;
}

void 				model::model::center()
{

	const vec3		offset = min + (max - min) / vec3(2.f);

	for (auto &mesh : meshes)
	{
		for (auto &vertex : mesh->vertices)
			vertex.position -= offset;

		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh::vertex), mesh->vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}