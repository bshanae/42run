#include "widget.h"

using namespace				UI;

void						widget::set_texture(unique<model::texture> &texture)
{
	vector<model::vertex>	vertices;
	vector<unsigned int>	indices;
	unique<model::material>	material;

	vertices.emplace_back(vec3(-1.f, 1.f, 0.f), vec3(), vec2(0.f, 1.f));
	vertices.emplace_back(vec3(-1.f, -1.f, 0.f), vec3(), vec2(0.f, 0.f));
	vertices.emplace_back(vec3(+1.f, +1.f, 0.f), vec3(), vec2(1.f, 1.f));
	vertices.emplace_back(vec3(+1.f, -1.f, 0.f), vec3(), vec2(1.f, 0.f));

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);

	material = make_unique<model::material>();
	material->textures.ambient = move(texture);

	model = make_shared<model::model>();
	model->emplace(vertices, indices, material);

	instance = make_shared<model::instance>(model);
	render_target(instance);
}