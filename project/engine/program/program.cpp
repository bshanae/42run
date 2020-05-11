#include "program.h"

#include "engine/program/shader.h"

using namespace		engine::program;

					program::program(const path &vertex_source, const path &fragment_source)
{
	object = glCreateProgram();

	shader			vertex_shader(shader::type::vertex, vertex_source);
	shader			fragment_shader(shader::type::fragment, fragment_source);

	glAttachShader(object, vertex_shader.object);
	glAttachShader(object, fragment_shader.object);

	glLinkProgram(object);

	GLint			success;
	GLchar			log[512];

	glGetProgramiv(object, GL_LINK_STATUS, &success);
	if (not success)
	{
		glGetProgramInfoLog(object, 512, nullptr, log);
		std::cout << "OPENGL ERROR" << std::endl;
		std::cout << log << std::endl;
		common::error::raise(common::error::id::program_compilation_error);
	}
}

					program::~program()
{
	glDeleteProgram(object);
}
