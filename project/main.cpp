#include "engine/engine.h"

class				renderer : public engine::renderer
{
public :
					renderer() : model("/Users/belchenkovova/Desktop/cube/cube.obj")
					{}
					~renderer() override = default;

	void			render() override
	{
		program.use(true);

		uniforms.projection->save(camera.projection_matrix());
		uniforms.view->save(camera.view_matrix());

		engine::renderer::render(model);

		program.use(false);
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

	engine::camera::initial_position = engine::vec3(0.f, 0.f, 2.f);
	engine::camera::movement_speed = 1.f;
	engine::camera::rotation_speed = .3f;
	engine::camera::near_plane = 0.1f;
	engine::camera::far_plane = 100.f;

	engine::core::initialize();

	renderer		renderer;

	engine::core::attach_renderer(renderer);
	engine::core::start();

	return (0);
}
