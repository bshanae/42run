#include "renderer.h"

using namespace		game;

void				renderer::render(const shared<game_object::game_object> &object) const
{
	if (not object->is_enabled)
		return ;

	program->use(true);

	uniforms.group.scaling.upload(mat4(1.f));
	uniforms.group.translation.upload(mat4(1.f));
	uniforms.group.rotation.upload(mat4(1.f));

	auto			render_targets = game_object::reader::render_targets(object);

	for (const auto &instance : render_targets.instances)
		render(instance);
	for (const auto &group : render_targets.groups)
		render(group);

	program->use(false);
}

void				renderer::render(const shared<model::instance> &instance) const
{
	auto			&model = model::reader::model(instance);
	auto			&skeleton = model::reader::skeleton(model);
	auto			&bones = model::reader::bones(skeleton);

	if (bones.empty())
		uniforms.does_mesh_have_bones.upload(0);
	else
	{
		mat4		transformation;

		uniforms.does_mesh_have_bones.upload(1);

		for (int i = 0; i < model::skeleton::bones_limit; i++)
		{
			if (i >= bones.size())
				break ;
			else
			{
				transformation = mat4(1.0f);
				transformation *= bones[i]->get_parents_transformation();
				transformation *= converter::to_glm(bones[i]->node->mTransformation);
				transformation *= bones[i]->offset;
				uniforms.bones_transformations[i].upload(transformation);
			}
		}
	}

	uniforms.instance.scaling.upload(model::reader::scaling(instance));
	uniforms.instance.translation.upload(model::reader::translation(instance));
	uniforms.instance.rotation.upload(model::reader::rotation(instance));

	glPolygonMode(GL_FRONT_AND_BACK, model::reader::is_hollow(instance) ? GL_LINE : GL_FILL);

	for (auto &mesh : model::reader::meshes(model))
	{
		auto		&material = model::reader::material(mesh);

		uniforms.material.unite.ambient.upload(material->unite.ambient);
		uniforms.material.unite.diffuse.upload(material->unite.diffuse);
		uniforms.material.unite.specular.upload(material->unite.specular);
		uniforms.material.unite.emission.upload(material->unite.emission);
		uniforms.material.unite.alpha.upload(material->unite.alpha);

		uniforms.material.textures.ambient.is_valid.upload(material->textures.ambient != nullptr);
		if (material->textures.ambient)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model::reader::object(material->textures.ambient));
		}

		uniforms.material.textures.diffuse.is_valid.upload(material->textures.diffuse != nullptr);
		if (material->textures.diffuse)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, model::reader::object(material->textures.diffuse));
		}

		uniforms.material.textures.specular.is_valid.upload(material->textures.specular != nullptr);
		if (material->textures.specular)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, model::reader::object(material->textures.specular));
		}

		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(model::reader::VAO(mesh));
		glDrawElements(GL_TRIANGLES, model::reader::indices(mesh).size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void				renderer::render(const shared<model::group> &group) const
{
	uniforms.group.scaling.upload(model::reader::scaling(group));
	uniforms.group.translation.upload(model::reader::translation(group));
	uniforms.group.rotation.upload(model::reader::rotation(group));

	for (const auto &instance : model::reader::instances(group))
		render(instance);
}