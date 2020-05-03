#include "renderer.h"

#include "engine/core/core.h"

using namespace		engine;

					renderer::renderer() :
					program("project/resources/vertex.glsl", "project/resources/fragment.glsl")
{
	uniforms.projection.emplace(program.find_uniform_location("uniform_projection"));
	uniforms.view.emplace(program.find_uniform_location("uniform_view"));

	uniforms.material.colors.ambient.emplace(program.find_uniform_location("uniform_material.colors.ambient"));
	uniforms.material.colors.diffuse.emplace(program.find_uniform_location("uniform_material.colors.diffuse"));
	uniforms.material.colors.specular.emplace(program.find_uniform_location("uniform_material.colors.specular"));

	uniforms.material.textures.diffuse.is_valid.emplace(program.find_uniform_location("uniform_material.textures.diffuse.is_valid"));
	uniforms.material.textures.diffuse.value.emplace(program.find_uniform_location("uniform_material.textures.diffuse.value"));

	uniforms.material.textures.specular.is_valid.emplace(program.find_uniform_location("uniform_material.textures.specular.is_valid"));
	uniforms.material.textures.specular.value.emplace(program.find_uniform_location("uniform_material.textures.specular.value"));

	uniforms.light.camera.emplace(program.find_uniform_location("uniform_light.camera"));
	uniforms.light.position.emplace(program.find_uniform_location("uniform_light.position"));

	program.use(true);

	uniforms.light.position->save(vec3(0, 5, 5));

	program.use(false);
}

void				renderer::render(initializer_list<const reference_wrapper<model>> models)
{
	program.use(true);

	uniforms.projection->save(scene.camera.projection_matrix());
	uniforms.view->save(scene.camera.view_matrix());

	uniforms.light.camera->save(scene.camera.position);

	for (auto model : models)
		render_model(model);

	program.use(false);

	request = false;
}

void				renderer::render_model(const model &model)
{
	for (auto &mesh : model.meshes)
	{
		uniforms.material.colors.ambient->save(mesh->material->colors.ambient);
		uniforms.material.colors.diffuse->save(mesh->material->colors.diffuse);
		uniforms.material.colors.specular->save(mesh->material->colors.specular);

		uniforms.material.textures.diffuse.is_valid->save(mesh->material->textures.diffuse.has_value());
		if (mesh->material->textures.diffuse)
		{
			auto	value = mesh->material->textures.diffuse->object;

			glActiveTexture(GL_TEXTURE0);
			uniforms.material.textures.diffuse.value->save(0);
			glBindTexture(GL_TEXTURE_2D, value);
		}

		uniforms.material.textures.specular.is_valid->save(mesh->material->textures.specular.has_value());
		if (mesh->material->textures.specular)
		{
			auto	value = mesh->material->textures.specular->object;

			glActiveTexture(GL_TEXTURE1);
			uniforms.material.textures.specular.value->save(1);
			glBindTexture(GL_TEXTURE_2D, value);
		}

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
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
		case engine::key::letter_a :
			camera.move(camera::movement::left);
			break ;

		case engine::key::letter_d :
			camera.move(camera::movement::right);
			break ;

		case engine::key::letter_w :
			camera.move(camera::movement::forth);
			break ;

		case engine::key::letter_s :
			camera.move(camera::movement::back);
			break ;

		case engine::key::letter_q :
			camera.move(camera::movement::up);
			break ;

		case engine::key::letter_e :
			camera.move(camera::movement::down);
			break ;

		case engine::key::left :
			camera.rotate(camera::rotation::left);
			break ;

		case engine::key::right :
			camera.rotate(camera::rotation::right);
			break ;

		case engine::key::up :
			camera.rotate(camera::rotation::up);
			break ;

		case engine::key::down :
			camera.rotate(camera::rotation::down);
			break ;

		default :
			return ;
	}
	request = true;
}