#include "common/common.h"
#include "engine/engine.h"

class				triangle : public engine::model<>
{
public :
					triangle()
	{
		GLfloat		vertices[] = {
			// Первый треугольник
			0.5f,  0.5f, 0.0f,  // Верхний правый угол
			0.5f, -0.5f, 0.0f,  // Нижний правый угол
			-0.5f,  0.5f, 0.0f,  // Верхний левый угол
			// Второй треугольник
			0.5f, -0.5f, 0.0f,  // Нижний правый угол
			-0.5f, -0.5f, 0.0f,  // Нижний левый угол
			-0.5f,  0.5f, 0.0f   // Верхний левый угол
		};

		vbos.vertices.copy(vertices + 0, vertices + 18);
	}
};

class				renderer : public engine::renderer
{
public :
					renderer() :
					program("project/resources/vertex.glsl", "project/resources/fragment.glsl")
	{}
					~renderer() override = default;

	void			render() override
	{

		draw(triangle);
	}

	triangle		triangle;

	engine::camera	camera;
	engine::program	program;
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

	engine::camera::initial_position = engine::vec3(0.f, 0.f, 5.f);
	engine::camera::movement_speed = 1.f;
	engine::camera::rotation_speed = .3f;
	engine::camera::near_plane = .1f;
	engine::camera::far_plane = 100.f;

	engine::core::initialize();

	renderer		renderer;

	engine::core::attach_renderer(renderer);
	engine::core::start();

	return (0);
}