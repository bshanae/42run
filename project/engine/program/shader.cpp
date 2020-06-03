#include "shader.h"

using namespace				engine::program;

shader::shader(type type, const path &source)
{
	auto					write_file_to_stream = [](stringstream &stream, const path &path)
	{
		ifstream			file;

		file.open(path);
		if (not file.is_open())
			error::raise(error::id::shader_file_error);

		stream << file.rdbuf();

		file.close();
	};

	std::stringstream		stream;

	stream << "#version " << settings().glsl_version;
	if (auto path = settings().glsl_path / "shared.h"; exists(path))
		write_file_to_stream(stream, path);
	write_file_to_stream(stream, source);

	const string			string = stream.str();
	const char				*raw_string = string.data();

	object = glCreateShader(static_cast<GLuint>(type));
	glShaderSource(object, 1, &raw_string, nullptr);
	glCompileShader(object);

	GLint					success;

	glGetShaderiv(object, GL_COMPILE_STATUS, &success);

#if DEBUG_STATE
	GLchar					log[1024];

	if (not success)
	{
		glGetShaderInfoLog(object, 1024, nullptr, log);
		std::cout << "DEBUG // GLSL SHADER" << std::endl << std::endl;
		std::cout << raw_string << std::endl << std::endl;
		std::cout << "DEBUG // GLSL OUTPUT" << std::endl << std::endl;
		std::cout << log << std::endl << std::endl;
		error::raise(error::id::shader_compilation_error);
	}
#else
	if (not success)
		error::raise(error::id::shader_compilation_error);
#endif
}
shader::~shader()
{
	glDeleteShader(object);
}