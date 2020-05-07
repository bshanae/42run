#pragma once

#include <unordered_map>
#include <exception>

namespace									exception
{
	enum class								id
	{
		standard,
		unimplemented_virtual_method,
		empty_global_object,
		GLFW_error,
		GLAD_error,
		ASSIMP_error,
		shader_reading_error,
		shader_compilation_error,
		uniform_bad_value,
		uniform_bad_type,
		program_compilation_error,
		texture_creation_error,
		texture_bad_format,
		event_bad_type
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::standard,                     "42run : Standard exception"},
		{id::unimplemented_virtual_method, "42run : A virtual method is not implemented"},
		{id::empty_global_object,       	"42run : Global object is not initialized"},
		{id::GLFW_error,                	"42run, Engine : GLFW error"},
		{id::GLAD_error,                	"42run, Engine : GLAD error"},
		{id::ASSIMP_error,              	"42run, Engine : ASSIMP error"},
		{id::shader_reading_error,      	"42run, Engine, Shader : Can't read source file"},
		{id::shader_compilation_error,  	"42run, Engine, Shader : Can't compile shader"},
		{id::uniform_bad_value,         	"42run, Engine, Uniform : Bad uniform value, maybe uniform is not initialized"},
		{id::uniform_bad_type,          	"42run, Engine, Uniform : Bad uniform type"},
		{id::program_compilation_error, 	"42run, Engine, Program : Can't compile program"},
		{id::texture_creation_error,    	"42run, Engine, Texture : Can't create texture"},
		{id::texture_bad_format,        	"42run, Engine, Texture : Bad format"},
		{id::event_bad_type,            	"42run, Engine, Event : Bad type"}
	};

	template								<id id>
	class 									exception : public std::exception
	{
	public :
											exception() = default;
											~exception() override = default;

		[[nodiscard]] const char			*what() const noexcept override
		{
			auto							message = messages.find(id);

			assert(message != messages.end());
			return (message->second);
		}
	};
}