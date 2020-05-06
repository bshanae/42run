#pragma once

#include <unordered_map>
#include <exception>

namespace									exception
{
	enum class								id
	{
		standard,
		unimplemented_virtual_method,
		GLFW,
		GLAD,
		ASSIMP,
		shader_reading,
		shader_compilation,
		uniform_value,
		uniform_type,
		program_compilation,
		texture_creation,
		texture_format,
		event_bad_type
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::standard,						"42run : Standard exception"},
		{id::unimplemented_virtual_method,	"42run : An virtual method is not implemented"},
		{id::GLFW,                         	"42run, Engine : GLFW error"},
		{id::GLAD,							"42run, Engine : GLAD error"},
		{id::ASSIMP,						"42run, Engine : ASSIMP error"},
		{id::shader_reading,				"42run, Engine, Shader : Can't read source file"},
		{id::shader_compilation,			"42run, Engine, Shader : Can't compile shader"},
		{id::uniform_value,					"42run, Engine, Uniform : Bad uniform value, maybe uniform is not initialized"},
		{id::uniform_type,					"42run, Engine, Uniform : Bad uniform type"},
		{id::program_compilation,			"42run, Engine, Program : Can't compile program"},
		{id::texture_creation,				"42run, Engine, Texture : Can't create texture"},
		{id::texture_format,				"42run, Engine, Texture : Bad format"},
		{id::event_bad_type,				"42run, Engine, Event : Bad type"}
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