#include "engine/engine.h"

engine::path		triangle = "/Users/belchenkovova/Desktop/triangle.obj";
engine::path		cube = "/Users/belchenkovova/Desktop/cube/cube.obj";

class				renderer : public engine::renderer
{
public :
					renderer() :
					model(cube)
					{}
					~renderer() override = default;

	void			render() override
	{
		program.use(true);

		uniforms.projection->save(camera.projection_matrix());
		uniforms.view->save(camera.view_matrix());

		engine::renderer::render(model);

		program.use(false);

		request = false;
	}

	engine::model	model;
};

int					main()
{
	engine::core::window_size = engine::ivec2(1280, 720);
	engine::core::window_name = "42run";
	engine::core::background = engine::vec3(0.1f, 0.1f, 0.1f);
	engine::core::use_multisampling = false;
	engine::core::number_of_samples = 0;
	engine::core::use_blending = false;
	engine::core::use_depth_test = true;

	engine::camera::initial_position = engine::vec3(0.f, 0.f, 5.f);
	engine::camera::movement_speed = .3f;
	engine::camera::rotation_speed = 1.f;
	engine::camera::near_plane = 0.1f;
	engine::camera::far_plane = 100.f;

	engine::core::initialize();

	renderer		renderer;

	engine::core::generate_callback(engine::event::type::key_press, &renderer::callback, &renderer);
	engine::core::generate_callback(engine::event::type::key_hold, &renderer::callback, &renderer);
	engine::core::attach_renderer(renderer);

	engine::core::execute();

	return (0);
}
