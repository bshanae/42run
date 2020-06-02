#include "renderer.h"

#include "engine/model/bone.h"

using namespace		engine;

void				renderer::render()
{
	request = false;

	program->use(true);

	uniforms.projection.upload(scene.camera.projection_matrix());
	uniforms.view.upload(scene.camera.view_matrix());

	uniforms.group.scaling.upload(mat4(1.f));
	uniforms.group.translation.upload(mat4(1.f));
	uniforms.group.rotation.upload(mat4(1.f));

	for (const auto &instance : targets.instances)
		render(instance);

	for (const auto &group : targets.groups)
		render(group);

	program->use(false);
}

void				renderer::render(const model::instance::ptr &instance)
{
	assert(instance);

	auto			&skeleton = instance->model->skeleton;

	if (skeleton->bones.empty())
		uniforms.does_mesh_have_bones.upload(0);
	else
	{
		mat4		transformation;

		uniforms.does_mesh_have_bones.upload(1);

		for (int i = 0; i < model::skeleton::bones_limit; i++)
		{
			if (i >= skeleton->bones.size())
				break ;
			else
			{
				transformation = mat4(1.0f);
				transformation *= skeleton->bones[i]->get_parents_transformation();
				transformation *= converter::to_glm(skeleton->bones[i]->node->mTransformation);
				transformation *= skeleton->bones[i]->offset;
				uniforms.bones_transformations[i].upload(transformation);
			}
		}
	}

	uniforms.instance.scaling.upload(instance->scaling);
	uniforms.instance.translation.upload(instance->translation);
	uniforms.instance.rotation.upload(instance->rotation);

	for (auto &mesh : instance->model->meshes)
	{
		uniforms.material.unite.ambient.upload(mesh->material->unite.ambient);
		uniforms.material.unite.diffuse.upload(mesh->material->unite.diffuse);
		uniforms.material.unite.specular.upload(mesh->material->unite.specular);
		uniforms.material.unite.emission.upload(mesh->material->unite.emission);
		uniforms.material.unite.alpha.upload(mesh->material->unite.alpha);

		uniforms.material.textures.ambient.is_valid.upload(mesh->material->textures.ambient != nullptr);
		if (mesh->material->textures.ambient)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.ambient->object);
		}

		uniforms.material.textures.diffuse.is_valid.upload(mesh->material->textures.diffuse != nullptr);
		if (mesh->material->textures.diffuse)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.diffuse->object);
		}

		uniforms.material.textures.specular.is_valid.upload(mesh->material->textures.specular != nullptr);
		if (mesh->material->textures.specular)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.specular->object);
		}

		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void				renderer::render(const model::group::ptr &group)
{
	uniforms.group.scaling.upload(group->scaling);
	uniforms.group.translation.upload(group->translation);
	uniforms.group.rotation.upload(group->rotation);

	for (const auto &instance : group->data)
		render(instance);
}