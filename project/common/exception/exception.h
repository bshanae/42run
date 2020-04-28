#pragma once

#include "common/namespace.h"

class										common::exception
{
public :

	enum class								id
	{
		standard,
		unimplemented_virtual_method,
		GLFW_error,
		GLEW_error,
		VAO_bad_type,
		shader_reading_error,
		shader_compilation_error,
		program_compilation_error
	};

	const std::map<id, const char *>		messages =
	{
		{id::standard,						"42run : Standard exception"},
		{id::unimplemented_virtual_method,	"42run : An virtual method is not implemented"},
		{id::GLFW_error,					"42run, Engine, Core : GLFW error"},
		{id::GLEW_error,					"42run, Engine, Core : GLEW error"},
		{id::VAO_bad_type,					"42run, Engine, VAO : Bad data type"},
		{id::shader_reading_error,			"42run, Engine, Shader : Can't read source file"},
		{id::shader_compilation_error,		"42run, Engine, Shader : Can't compile shader"},
		{id::program_compilation_error,		"42run, Engine, Program : Can't compile program"}
	};

private :
											exception() = default;
											~exception() = default;

	static exception						&instance()
	{
		static exception					exception;

		return (exception);
	}

	template							<enum id id>
	class 									object : public std::exception
	{
		friend class 						common::exception;

	private :
		explicit 							object(const char *message) :
											message(message) {}
	public :
											~object() override = default;

		[[nodiscard]] const char			*what() const noexcept override
		{
			return (message);
		}

	private :

		const char 							*message;
	};

public :

	template							<enum id id>
	static auto 							make_object()
	{
		auto 								&instance = exception::instance();
		auto								message = instance.messages.find(id);

		assert(message != instance.messages.end());
		return (object<id>(message->second));
	}
};