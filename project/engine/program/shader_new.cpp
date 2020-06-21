#include "shader.h"

using namespace				engine::program;

							shader::shader(type type, const path &source)
{
	auto					write_file_to_stream = [](stringstream &stream, const path &path)
	{
		ifstream			file;

		file.open(path);
		if (not file.is_open())
			class::raise(class::id::shader_file_error);

		stream << file.rdbuf();

		file.close();
	};

	std::stringstream		stream;

//	stream << "#version " << settings().glsl_version;
//	if (auto path = settings().glsl_path / "shared.h"; exists(path))
//		write_file_to_stream(stream, path);
	write_file_to_stream(stream, source);

	auto					read_file = [](const path &source)
	{
		std::ifstream		file;
		std::stringstream	stream;

		file.open(source);
		if (not file.is_open())
			class::raise(class::id::shader_file_error);

		stream << file.rdbuf();
		file.close();
		return (stream.str());
	};

//	const string			string = stream.str();
	const string			string = read_file(source);
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
		cout << "DEBUG // GLSL SHADER" << endl << endl;
		cout << raw_string << endl << endl;
		cout << "DEBUG // GLSL OUTPUT" << endl << endl;
		cout << log << endl << endl;
		class::raise(class::id::shader_compilation_error);
	}
#else
	if (not success)
		class::raise(class::id::shader_compilation_error);
#endif
}
							shader::~shader()
{
	glDeleteShader(object);
}