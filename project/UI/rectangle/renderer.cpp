#include "renderer.h"

#include "UI/rectangle/rectangle.h"
#include "UI/icon/icon.h"

using namespace		UI;

					rectangle::renderer::renderer()
{
	program = make_unique<engine::program::program>
	(
		sources().rectangle_vertex_shader,
		sources().rectangle_fragment_shader
	);

	uniforms.projection = program->make_uniform<mat4>("uniform_projection");
	uniforms.scaling = program->make_uniform<mat4>("uniform_scaling");
	uniforms.translation = program->make_uniform<mat4>("uniform_translation");
	uniforms.texture = program->make_uniform<int>("uniform_texture");
	uniforms.color = program->make_uniform<vec3>("uniform_color");
	uniforms.use_texture = program->make_uniform<int>("uniform_use_texture");

	auto			projection = glm::ortho
	(
		0.f,
		(float)engine::settings().window_size.x,
		(float)engine::settings().window_size.y,
		0.f
	);

	program->use(true);

	uniforms.texture.upload(0);
	uniforms.projection.upload(projection);

	program->use(false);
}

void				rectangle::renderer::render(const shared<engine::game_object::game_object> &object) const
{
	auto			rectangle = dynamic_pointer_cast<UI::rectangle::rectangle>(object);

	if (not rectangle)
	{
		warning::raise(warning::id::object_improper_type);
		return;
	}

	engine::core::default_settings();
	engine::core::show_polygon_back(true);

	program->use(true);

	for (const auto &instance : game_object::reader::render_targets(rectangle).instances)
		render(instance);

	program->use(false);
}

void				rectangle::renderer::render(const shared<model::instance> &instance) const
{
	auto			&model = model::reader::model(instance);

	uniforms.scaling.upload(model::reader::scaling(instance));
	uniforms.translation.upload(model::reader::translation(instance));

	for (auto &mesh : model::reader::meshes(model))
	{
		auto		&material = model::reader::material(mesh);

		if (material->textures.ambient)
		{
			glActiveTexture(GL_TEXTURE0);
			material->textures.ambient->use(true);
		}
		else
			uniforms.color.upload(material->unite.ambient);
		uniforms.use_texture.upload(material->textures.ambient != nullptr);

		glBindVertexArray(model::reader::VAO(mesh));
		glDrawElements(GL_TRIANGLES, model::reader::indices(mesh).size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}