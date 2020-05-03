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
}

void				renderer::render(const model &model)
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