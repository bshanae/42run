#include "model.h"

#include <limits>

using namespace		engine;

void				model::model::analyze()
{
	analyzed.min = vec3(+1.f * std::numeric_limits<float>::infinity());
	analyzed.max = vec3(-1.f * std::numeric_limits<float>::infinity());

	for (const auto &mesh : meshes)
		for (const auto &vertex : mesh->vertices)
		{
			analyzed.min = glm::min(analyzed.min, vertex.position);
			analyzed.max = glm::max(analyzed.max, vertex.position);
		}

	analyzed.size = analyzed.max - analyzed.min;
	analyzed.offset = analyzed.min + (analyzed.max - analyzed.min) / vec3(2.f);

	is_analyzed = true;
}

void 				model::model::center()
{
	if (not is_analyzed)
		warning::raise(warning::id::model_is_not_analyzed);

	for (auto &mesh : meshes)
	{
		for (auto &vertex : mesh->vertices)
			vertex.position -= analyzed.offset;

		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh::vertex), mesh->vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	is_centered = true;
}