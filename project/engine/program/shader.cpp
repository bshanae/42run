#include "shader.h"

using namespace			engine;

static string			read_file(const string &source)
{
	std::ifstream		file;
	std::stringstream	stream;

	file.open(source);
	if (not file.is_open())
		throw (exception::make_object<exception::id::shader_reading>());

	stream << file.rdbuf();
	file.close();
	return (stream.str());
}

						shader::shader(type type, const string &source)
{
	string				file = read_file(source);
	const char			*file_raw = file.c_str();

	object = glCreateShader(static_cast<GLuint>(type));
	glShaderSource(object, 1, &file_raw, nullptr);
	glCompileShader(object);

	GLint				success;
	GLchar				log[512];

	glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	if (not success)
	{
		glGetShaderInfoLog(object, 512, nullptr, log);
		cout << "/--------------------/ LOG /--------------------/" << endl << log << endl;
		throw (exception::make_object<exception::id::shader_compilation>());
	}
}

						shader::~shader()
{
	glDeleteShader(object);
}
