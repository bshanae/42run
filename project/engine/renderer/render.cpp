#include "renderer.h"

#include "engine/model/bone.h"

using namespace		engine;

void				renderer::render()
{
	global().revise();

	upload_camera_data();

	program->use(true);

	for (const auto &object : global().scene->objects)
	{
		if (not object->is_enabled)
			continue ;

		uniforms.group.scaling.upload(mat4(1.f));
		uniforms.group.translation.upload(mat4(1.f));
		uniforms.group.rotation.upload(mat4(1.f));

		for (const auto &instance : object->render_targets.instances)
			render(instance);

		for (const auto &group : object->render_targets.groups)
			render(group);
	}

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

	uniforms.instance.scaling.upload(instance->transformations.scaling);
	uniforms.instance.translation.upload(instance->transformations.translation);
	uniforms.instance.rotation.upload(instance->transformations.rotation);

	glPolygonMode(GL_FRONT_AND_BACK, instance->is_hollow ? GL_LINE : GL_FILL);

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
	uniforms.group.scaling.upload(group->transformations.scaling);
	uniforms.group.translation.upload(group->transformations.translation);
	uniforms.group.rotation.upload(group->transformations.rotation);

	for (const auto &instance : group->instances)
		render(instance);
}