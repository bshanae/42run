#include "renderer.h"

#include "UI/font/font.h"
#include "UI/font/manager.h"

using namespace		UI;

					font::renderer::renderer()
{
	program = make_unique<engine::program::program>
	(
		sources().vertex_shader,
		sources().fragment_shader
	);

	uniforms.texture = program->make_uniform<int>("uniform_texture");
	uniforms.color = program->make_uniform<vec3>("uniform_color");
	uniforms.projection = program->make_uniform<mat4>("uniform_projection");
	uniforms.scaling = program->make_uniform<mat4>("uniform_scaling");
	uniforms.translation = program->make_uniform<mat4>("uniform_translation");

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

void				font::renderer::render(const shared<engine::game_object::game_object> &object) const
{
	engine::core::default_settings();
	engine::core::show_polygon_back(true);
//	engine::core::use_depth_test(false);

	program->use(true);

	if (not UI::font::manager::instance()->font)
		error::raise(error::id::global_font_not_loaded);
	uniforms.color.upload(UI::font::manager::instance()->font->color);

	for (const auto &instance : game_object::reader::render_targets(object).instances)
		render(instance);

	program->use(false);
}

void				font::renderer::render(const shared<model::instance> &instance) const
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
			warning::raise(warning::id::object_without_texture);

		glBindVertexArray(model::reader::VAO(mesh));
		glDrawElements(GL_TRIANGLES, model::reader::indices(mesh).size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}