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

	uniforms.light.camera = program->make_uniform<vec3>("uniform_light.camera");
	uniforms.light.position = program->make_uniform<vec3>("uniform_light.position");

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
	uniforms.light.position.save(LIGHT_POSITION);

	uniforms.material.textures.ambient.value.save(0);
	uniforms.material.textures.diffuse.value.save(1);
	uniforms.material.textures.specular.value.save(2);

	program->use(false);
}

void				renderer::render()
{
	request = false;

	program->use(true);

	uniforms.projection.save(scene.camera.projection_matrix());
	uniforms.view.save(scene.camera.view_matrix());

	uniforms.light.camera.save(scene.camera.position);

	uniforms.group.scaling.save(mat4(1.f));
	uniforms.group.translation.save(mat4(1.f));
	uniforms.group.rotation.save(mat4(1.f));

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

	uniforms.instance.scaling.save(instance->scaling);
	uniforms.instance.translation.save(instance->translation);
	uniforms.instance.rotation.save(instance->rotation);

	for (auto &mesh : instance->model->meshes)
	{
		uniforms.material.unite.ambient.save(mesh->material->unite.ambient);
		uniforms.material.unite.diffuse.save(mesh->material->unite.diffuse);
		uniforms.material.unite.specular.save(mesh->material->unite.specular);
		uniforms.material.unite.emission.save(mesh->material->unite.emission);
		uniforms.material.unite.alpha.save(mesh->material->unite.alpha);

		uniforms.material.textures.ambient.is_valid.save(mesh->material->textures.ambient != nullptr);
		if (mesh->material->textures.ambient)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.ambient->object);
		}

		uniforms.material.textures.diffuse.is_valid.save(mesh->material->textures.diffuse != nullptr);
		if (mesh->material->textures.diffuse)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->material->textures.diffuse->object);
		}

		uniforms.material.textures.specular.is_valid.save(mesh->material->textures.specular != nullptr);
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
	uniforms.group.scaling.save(group->scaling);
	uniforms.group.translation.save(group->translation);
	uniforms.group.rotation.save(group->rotation);

	for (const auto &instance : group->data)
		render(instance);
}

void				renderer::callback()
{
	const auto		&event = core::receive_event();
	auto			key = event.read_key();
	auto			&camera = scene.camera;

	static vec3 	light_position = LIGHT_POSITION;
	bool			light_changed = false;

	static bool		wireframe_mod = false;

	program->use(true);

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

#define SHIFT 2


		case engine::interface::key::letter_j :
			light_position.x -= SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		case engine::interface::key::letter_l :
			light_position.x += SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		case engine::interface::key::letter_i :
			light_position.z -= SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		case engine::interface::key::letter_k :
			light_position.z += SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		case engine::interface::key::letter_u :
			light_position.y += SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		case engine::interface::key::letter_o :
			light_position.y -= SHIFT;
			uniforms.light.position.save(light_position);
			light_changed = true;
			break ;

		default :
			program->use(false);
			return ;
	}

	if (light_changed)
		std::cerr << "Light position : " << glm::to_string(light_position) << std::endl;

	program->use(false);
	request = true;
}