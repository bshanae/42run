#include "renderer.h"

#include "engine/core/core.h"
#include "engine/model/bone.h"

using namespace		engine;

#warning "Debug only"
//#define LIGHT_POSITION vec3(-200, 250, 100)
#define LIGHT_POSITION vec3(0, 30, 0)

					renderer::renderer()
{
	auto			vertex = settings().glsl_path / "main.vertex.glsl";
	auto			fragment = settings().glsl_path / "main.fragment.glsl";

	program = engine::program::program::make_ptr(vertex, fragment);

	uniforms.projection = program->make_uniform<mat4>("uniform_projection");
	uniforms.view = program->make_uniform<mat4>("uniform_view");

	uniforms.material.unite.ambient = program->make_uniform<vec3>("uniform_material.unite.ambient");
	uniforms.material.unite.diffuse = program->make_uniform<vec3>("uniform_material.unite.diffuse");
	uniforms.material.unite.specular = program->make_uniform<vec3>("uniform_material.unite.specular");
	uniforms.material.unite.emission = program->make_uniform<vec3>("uniform_material.unite.emission");
	uniforms.material.unite.alpha = program->make_uniform<float>("uniform_material.unite.alpha");

	uniforms.material.textures.ambient.is_valid = program->make_uniform<int>("uniform_material.textures.ambient.is_valid");
	uniforms.material.textures.ambient.value = program->make_uniform<int>("uniform_material.textures.ambient.value");

	uniforms.material.textures.diffuse.is_valid = program->make_uniform<int>("uniform_material.textures.diffuse.is_valid");
	uniforms.material.textures.diffuse.value = program->make_uniform<int>("uniform_material.textures.diffuse.value");

	uniforms.material.textures.specular.is_valid = program->make_uniform<int>("uniform_material.textures.specular.is_valid");
	uniforms.material.textures.specular.value = program->make_uniform<int>("uniform_material.textures.specular.value");

	uniforms.camera_position = program->make_uniform<vec3>("uniform_camera_position");

	uniforms.light.size = program->make_uniform<int>("uniform_light.size");

	for (int i = 0; i < SHARED_LIGHTS_CAPACITY; i++)
	{
		uniforms.light.direction_or_position[i] = program->make_uniform<vec4>("uniform_light.direction_or_position[" + to_string(i) + "]");
		uniforms.light.color[i] = program->make_uniform<vec3>("uniform_light.color[" + to_string(i) + "]");
	}

	uniforms.does_mesh_have_bones = program->make_uniform<int>("uniform_does_mesh_have_bones");
	for (int i = 0; i < model::skeleton::bones_limit; i++)
		uniforms.bones_transformations[i] = program->make_uniform<mat4>("uniform_bones_transformations[" + std::to_string(i) + "]");

	uniforms.instance.scaling = program->make_uniform<mat4>("uniform_instance.scaling");
	uniforms.instance.translation = program->make_uniform<mat4>("uniform_instance.translation");
	uniforms.instance.rotation = program->make_uniform<mat4>("uniform_instance.rotation");

	uniforms.group.scaling = program->make_uniform<mat4>("uniform_group.scaling");
	uniforms.group.translation = program->make_uniform<mat4>("uniform_group.translation");
	uniforms.group.rotation = program->make_uniform<mat4>("uniform_group.rotation");

	program->use(true);

	#warning "Debug only"
//	uniforms.light.position.upload(LIGHT_POSITION);

	uniforms.material.textures.ambient.value.upload(0);
	uniforms.material.textures.diffuse.value.upload(1);
	uniforms.material.textures.specular.value.upload(2);

	program->use(false);
}

void 				renderer::upload_camera_data()
{
	program->use(true);

	uniforms.camera_position.upload(scene.camera.position);

	program->use(false);
}

void 				renderer::upload_light_data()
{
	program->use(true);

	uniforms.light.size.upload(light_data.size);

	for (int i = 0; i < SHARED_LIGHTS_CAPACITY; i++)
	{
		uniforms.light.direction_or_position[i].upload(light_data.direction_or_position[i]);
		uniforms.light.color[i].upload(light_data.color[i]);
	}

	program->use(false);
}

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

void				renderer::callback()
{
	const auto		&event = core::receive_event();
	auto			key = event.read_key();
	auto			&camera = scene.camera;

	static bool		wireframe_mod = false;

	switch (key)
	{
		case engine::interface::key::letter_a :
			camera.move(scene::camera::movement::left);
			upload_camera_data();
			break ;

		case engine::interface::key::letter_d :
			camera.move(scene::camera::movement::right);
			upload_camera_data();
			break ;

		case engine::interface::key::letter_w :
			camera.move(scene::camera::movement::forth);
			upload_camera_data();
			break ;

		case engine::interface::key::letter_s :
			camera.move(scene::camera::movement::back);
			upload_camera_data();
			break ;

		case engine::interface::key::letter_q :
			camera.move(scene::camera::movement::up);
			upload_camera_data();
			break ;

		case engine::interface::key::letter_e :
			camera.move(scene::camera::movement::down);
			upload_camera_data();
			break ;

		case engine::interface::key::left :
			camera.rotate(scene::camera::rotation::left);
			upload_camera_data();
			break ;

		case engine::interface::key::right :
			camera.rotate(scene::camera::rotation::right);
			upload_camera_data();
			break ;

		case engine::interface::key::up :
			camera.rotate(scene::camera::rotation::up);
			upload_camera_data();
			break ;

		case engine::interface::key::down :
			camera.rotate(scene::camera::rotation::down);
			upload_camera_data();
			break ;

		case engine::interface::key::enter :
			for (auto &instance : targets.instances)
				if (instance->model->skeleton->animation)
					instance->model->skeleton->update();
			break ;

#warning "Debug only"
		case engine::interface::key::letter_x :
			wireframe_mod = not wireframe_mod;
			if (wireframe_mod)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break ;

		default :
			return ;
	}

	request = true;
}