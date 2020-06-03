#include "renderer.h"

using namespace		engine;

void				renderer::initialize_data()
{
	auto			vertex = settings().glsl_path / "main.vertex.glsl";
	auto			fragment = settings().glsl_path / "main.fragment.glsl";

	program = engine::program::program::make_ptr(vertex, fragment);

//					MATRICES

	uniforms.projection = program->make_uniform<mat4>("uniform_projection");
	uniforms.view = program->make_uniform<mat4>("uniform_view");

//					MATERIAL

	uniforms.material.unite.ambient = program->make_uniform<vec3>("uniform_material.unite.ambient");
	uniforms.material.unite.diffuse = program->make_uniform<vec3>("uniform_material.unite.diffuse");
	uniforms.material.unite.specular = program->make_uniform<vec3>("uniform_material.unite.specular");
	uniforms.material.unite.emission = program->make_uniform<vec3>("uniform_material.unite.emission");
	uniforms.material.unite.alpha = program->make_uniform<float>("uniform_material.unite.alpha");

//					TEXTURES

	uniforms.material.textures.ambient.is_valid = program->make_uniform<int>("uniform_material.textures.ambient.is_valid");
	uniforms.material.textures.ambient.value = program->make_uniform<int>("uniform_material.textures.ambient.value");

	uniforms.material.textures.diffuse.is_valid = program->make_uniform<int>("uniform_material.textures.diffuse.is_valid");
	uniforms.material.textures.diffuse.value = program->make_uniform<int>("uniform_material.textures.diffuse.value");

	uniforms.material.textures.specular.is_valid = program->make_uniform<int>("uniform_material.textures.specular.is_valid");
	uniforms.material.textures.specular.value = program->make_uniform<int>("uniform_material.textures.specular.value");

//					SCENE

	uniforms.scene.camera_position = program->make_uniform<vec3>("uniform_scene.camera_position");

	uniforms.scene.lights_size = program->make_uniform<int>("uniform_scene.lights_size");

	for (int i = 0; i < SHARED_LIGHTS_CAPACITY; i++)
	{
		uniforms.scene.lights[i].type = program->make_uniform<int>("uniform_scene.lights[" + to_string(i) + "].type");
		uniforms.scene.lights[i].data = program->make_uniform<vec3>("uniform_scene.lights[" + to_string(i) + "].data");
		uniforms.scene.lights[i].color = program->make_uniform<vec3>("uniform_scene.lights[" + to_string(i) + "].color");
		uniforms.scene.lights[i].power = program->make_uniform<float>("uniform_scene.lights[" + to_string(i) + "].power");
	}

//					SKELETON

	uniforms.does_mesh_have_bones = program->make_uniform<int>("uniform_does_mesh_have_bones");
	for (int i = 0; i < model::skeleton::bones_limit; i++)
		uniforms.bones_transformations[i] = program->make_uniform<mat4>("uniform_bones_transformations[" + std::to_string(i) + "]");

//					INSTANCE

	uniforms.instance.scaling = program->make_uniform<mat4>("uniform_instance.scaling");
	uniforms.instance.translation = program->make_uniform<mat4>("uniform_instance.translation");
	uniforms.instance.rotation = program->make_uniform<mat4>("uniform_instance.rotation");

//					GROUP

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
	auto 			scene = global().scene;

	global().revise();
	program->use(true);
	uniforms.projection.upload(scene->camera.projection_matrix());
	uniforms.view.upload(scene->camera.view_matrix());
	uniforms.scene.camera_position.upload(scene->camera.position);
	program->use(false);
}

void 				renderer::upload_light_data()
{
	auto			scene = global().scene;

	global().revise();
	program->use(true);
	uniforms.scene.lights_size.upload(scene->lights_size);
	for (int i = 0; i < SHARED_LIGHTS_CAPACITY; i++)
	{
		uniforms.scene.lights[i].type.upload((int)scene->lights[i].type);
		uniforms.scene.lights[i].data.upload(scene->lights[i].data);
		uniforms.scene.lights[i].color.upload(scene->lights[i].color);
		uniforms.scene.lights[i].power.upload(scene->lights[i].power);
	}
	program->use(false);
}