#include "renderer.h"

#include "UI/rectangle/rectangle.h"
#include "UI/icon/icon.h"

using namespace		UI;

					icon::renderer::renderer()
{
	program = make_unique<engine::program::program>
	(
		sources().icon_vertex_shader,
		sources().icon_fragment_shader
	);

	uniforms.texture = program->make_uniform<int>("uniform_texture");
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

void				icon::renderer::render(const shared<engine::game_object::game_object> &object) const
{
	auto			icon = dynamic_pointer_cast<UI::icon::icon>(object);

	if (not icon)
	{
		warning::raise(warning::id::object_is_not_an_icon);
		return;
	}

	auto			rectangle = icon->rectangle;
	auto			rectangle_as_object = dynamic_pointer_cast<game_object::game_object>(rectangle);
	auto			targets = game_object::reader::render_targets(rectangle_as_object);

	engine::core::default_settings();
	engine::core::show_polygon_back(true);

	program->use(true);

	for (const auto &instance : targets.instances)
		render(instance);

	program->use(false);
}

void				icon::renderer::render(const shared<model::instance> &instance) const
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