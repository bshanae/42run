#include "renderer.h"

#include "engine/core/core.h"
#include "engine/model/bone.h"

using namespace		engine;

					renderer::renderer() :
					program("project/resources/vertex.glsl", "project/resources/fragment.glsl")
{
	uniforms.projection = program.make_uniform<mat4>("uniform_projection");
	uniforms.view = program.make_uniform<mat4>("uniform_view");

	uniforms.material.colors.ambient = program.make_uniform<vec3>("uniform_material.colors.ambient");
	uniforms.material.colors.diffuse = program.make_uniform<vec3>("uniform_material.colors.diffuse");
	uniforms.material.colors.specular = program.make_uniform<vec3>("uniform_material.colors.specular");

	uniforms.material.textures.diffuse.is_valid = program.make_uniform<int>("uniform_material.textures.diffuse.is_valid");
	uniforms.material.textures.diffuse.value = program.make_uniform<int>("uniform_material.textures.diffuse.value");

	uniforms.material.textures.specular.is_valid = program.make_uniform<int>("uniform_material.textures.specular.is_valid");
	uniforms.material.textures.specular.value = program.make_uniform<int>("uniform_material.textures.specular.value");

	uniforms.light.camera = program.make_uniform<vec3>("uniform_light.camera");
	uniforms.light.position = program.make_uniform<vec3>("uniform_light.position");

	uniforms.does_mesh_have_bones = program.make_uniform<int>("uniform_does_mesh_have_bones");
	for (int i = 0; i < model::skeleton::bones_limit; i++)
		uniforms.bones_transformations[i] = program.make_uniform<mat4>("uniform_bones_transformations[" + std::to_string(i) + "]");

	uniforms.instance.scaling = program.make_uniform<mat4>("uniform_instance.scaling");
	uniforms.instance.translation = program.make_uniform<mat4>("uniform_instance.translation");
	uniforms.instance.rotation = program.make_uniform<mat4>("uniform_instance.rotation");

	program.use(true);

	uniforms.light.position.save(vec3(0, 5000, 0));

	uniforms.material.textures.diffuse.value.save(0);
	uniforms.material.textures.specular.value.save(1);

	program.use(false);
}

void				renderer::render()
{
	request = false;

	program.use(true);

	uniforms.projection.save(scene.camera.projection_matrix());
	uniforms.view.save(scene.camera.view_matrix());

	uniforms.light.camera.save(scene.camera.position);

	for (const auto &model : models)
		render(model);

	program.use(false);
}

void				renderer::render(const model::instance::ptr &model)
{
	auto			&skeleton = model->model->skeleton;

	if (skeleton->bones.empty())
		uniforms.does_mesh_have_bones.save(0);
	else
	{
		mat4		transformation;

		uniforms.does_mesh_have_bones.save(1);

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
				uniforms.bones_transformations[i].save(transformation);
			}
		}
	}

	uniforms.instance.scaling.save(model->scaling);
	uniforms.instance.translation.save(model->translation);
	uniforms.instance.rotation.save(model->rotation);

	for (auto &mesh : model->model->meshes)
	{
		uniforms.material.colors.ambient.save(mesh->material->colors.ambient);
		uniforms.material.colors.diffuse.save(mesh->material->colors.diffuse);
		uniforms.material.colors.specular.save(mesh->material->colors.specular);

		uniforms.material.textures.diffuse.is_valid.save(mesh->material->textures.diffuse != nullptr);
		if (mesh->material->textures.diffuse)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.diffuse->object);
		}

		uniforms.material.textures.specular.is_valid.save(mesh->material->textures.specular != nullptr);
		if (mesh->material->textures.specular)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.specular->object);
		}

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void				renderer::callback()
{
	const auto		&event = core::receive_event();
	auto			key = event.read_key();
	auto			&camera = scene.camera;

	switch (key)
	{
		case engine::interface::key::letter_a :
			camera.move(scene::camera::movement::left);
			break ;

		case engine::interface::key::letter_d :
			camera.move(scene::camera::movement::right);
			break ;

		case engine::interface::key::letter_w :
			camera.move(scene::camera::movement::forth);
			break ;

		case engine::interface::key::letter_s :
			camera.move(scene::camera::movement::back);
			break ;

		case engine::interface::key::letter_q :
			camera.move(scene::camera::movement::up);
			break ;

		case engine::interface::key::letter_e :
			camera.move(scene::camera::movement::down);
			break ;

		case engine::interface::key::left :
			camera.rotate(scene::camera::rotation::left);
			break ;

		case engine::interface::key::right :
			camera.rotate(scene::camera::rotation::right);
			break ;

		case engine::interface::key::up :
			camera.rotate(scene::camera::rotation::up);
			break ;

		case engine::interface::key::down :
			camera.rotate(scene::camera::rotation::down);
			break ;

		case engine::interface::key::enter :
			for (auto &model : models)
				if (model->model->skeleton->animation)
					model->model->skeleton->update();
			break ;

		default :
			return ;
	}
	request = true;
}