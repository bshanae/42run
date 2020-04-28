#include "engine/engine.h"

class				triangle : public engine::model<>
{
public :
					triangle()
	{
		GLfloat		vertices[] =
		{
			0.5f,  0.5f, 0.0f,  // Верхний правый угол
			0.5f, -0.5f, 0.0f,  // Нижний правый угол
			-0.5f, -0.5f, 0.0f,  // Нижний левый угол
			-0.5f,  0.5f, 0.0f   // Верхний левый угол
		};

		GLuint		indices[] =
		{
			0, 1, 3,   // Первый треугольник
			1, 2, 3    // Второй треугольник
		};

		this->vertices.copy(vertices + 0, vertices + 18);
		this->indices.copy(indices + 0, indices + 6);

		save();
	}
};

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

class				renderer : public engine::renderer
{
public :
					renderer() = default;
					~renderer() override = default;

	void			render() override
	{
		program.use(true);

		program.projection.save(camera.projection_matrix());
		program.view.save(camera.view_matrix());

		draw(triangle);

		program.use(false);
	}

	triangle		triangle;

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

	engine::camera::initial_position = engine::vec3(0.f, 0.f, 10.f);
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