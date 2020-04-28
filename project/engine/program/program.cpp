#include "program.h"

#include "engine/program/shader.h"

using namespace		engine;

					program::program(const string &vertex_source, const string &fragment_source)
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
		cout << "/--------------------/ LOG /--------------------/" << endl << log << endl;
		throw (exception::make_object<exception::id::program_compilation>());
	}
}

					program::~program()
{
	glDeleteProgram(object);
}
