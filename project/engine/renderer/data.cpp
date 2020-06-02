#include "renderer.h"

using namespace		engine;

void				renderer::initialize_data()
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
		uniforms.light.type[i] = program->make_uniform<int>("uniform_light.type[" + to_string(i) + "]");
		uniforms.light.data[i] = program->make_uniform<vec3>("uniform_light.data[" + to_string(i) + "]");
		uniforms.light.color[i] = program->make_uniform<vec3>("uniform_light.color[" + to_string(i) + "]");
		uniforms.light.intensity[i] = program->make_uniform<float>("uniform_light.intensity[" + to_string(i) + "]");
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
		uniforms.light.type[i].upload((int)light_data.type[i]);
		uniforms.light.data[i].upload(light_data.data[i]);
		uniforms.light.color[i].upload(light_data.color[i]);
		uniforms.light.intensity[i].upload(light_data.intensity[i]);
	}

	program->use(false);
}