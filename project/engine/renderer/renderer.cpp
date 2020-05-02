#include "renderer.h"

#include "engine/core/core.h"

using namespace		engine;

					renderer::renderer() :
					program("project/resources/vertex.glsl", "project/resources/fragment.glsl")
{
	uniforms.projection.emplace(program.find_uniform_location("uniform_projection"));
	uniforms.view.emplace(program.find_uniform_location("uniform_view"));
	uniforms.texture.emplace(program.find_uniform_location("uniform_texture"));
}

void				renderer::render(const model &model)
{
	cout << "render" << endl;
	for (auto &mesh : model.meshes)
	{
		unsigned int diffuse_index = 1;
		unsigned int specular_index = 1;

		for (unsigned int i = 0; i < mesh.textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			uniforms.texture->save(i);
			glBindTexture(GL_TEXTURE_2D, mesh.textures[i].object);
		}
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(mesh.VAO);
		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
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
	cout << "render request" << endl;
	request = true;
}