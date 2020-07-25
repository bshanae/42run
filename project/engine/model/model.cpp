#include "model.h"

#include <limits>

#include "engine/model/loader.h"

using namespace		engine;

					model::model::model(const string &source, flag_wrapper flags)
{
	if (not loader)
		loader = make_shared<engine::model::loader>();

	loader->load(*this, source, flags);
}

void				model::model::push(unique<engine::model::mesh> &mesh)
{
	meshes.push_back(move(mesh));
}

void				model::model::analyze()
{
	analysis.min = vec3(+1.f * std::numeric_limits<float>::infinity());
	analysis.max = vec3(-1.f * std::numeric_limits<float>::infinity());

	for (const auto &mesh : meshes)
		for (const auto &vertex : mesh->vertices)
		{
			analysis.min = glm::min(analysis.min, vertex.position);
			analysis.max = glm::max(analysis.max, vertex.position);
		}

	analysis.size = analysis.max - analysis.min;
	analysis.offset = analysis.min + (analysis.max - analysis.min) / vec3(2.f);

	is_analyzed = true;
}

void 				model::model::center()
{
	if (not is_analyzed)
		warning::raise(warning::id::model_is_not_analyzed);

	for (auto &mesh : meshes)
	{
		for (auto &vertex : mesh->vertices)
			vertex.position -= analysis.offset;

		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(vertex), mesh->vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	is_centered = true;
}