#include "engine/engine.h"

class				program : public engine::program
{
public :
					program() :
					engine::program("project/resources/vertex.glsl", "project/resources/fragment.glsl"),
					projection(object, "uniform_projection"),
					view(object, "uniform_view")
					{}

	using			uniform_mat4 = engine::uniform<glm::mat4>;

	uniform_mat4	projection;
	uniform_mat4	view;
};

#include "engine/model/mesh.h"

class				renderer : public engine::renderer
{
public :
					renderer() : model("/Users/belchenkovova/workspace/42run/IronMan/IronMan.obj") {}
					~renderer() override = default;

	void			render() override
	{
		program.use(true);

		program.projection.save(camera.projection_matrix());
		program.view.save(camera.view_matrix());

		model.Draw(program);

		program.use(false);
	}

	model			model;

	engine::camera	camera;
	class program	program;
};

int					main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.5f, 0.5f, 0.5f);
	engine::core::use_multisampling = false;
	engine::core::number_of_samples = 0;
	engine::core::use_blending = false;
	engine::core::use_depth_test = true;

	engine::camera::initial_position = engine::vec3(0.f, 0.f, 1000.f);
	engine::camera::movement_speed = 1.f;
	engine::camera::rotation_speed = .3f;
	engine::camera::near_plane = 10.f;
	engine::camera::far_plane = 10000.f;

	engine::core::initialize();

	renderer		renderer;

	engine::core::attach_renderer(renderer);
	engine::core::start();

	return (0);
}
