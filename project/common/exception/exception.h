#pragma once

#include "common/namespace.h"

class										common::exception
{
public :

	enum class								id
	{
		standard,
		unimplemented_virtual_method,
		GLFW,
		GLAD,
		VBO_resize_more_than_one,
		VBO_static,
		VAO_type,
		shader_reading,
		shader_compilation,
		uniform_creation,
		uniform_type,
		program_compilation
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::standard,                     "42run : Standard exception"},
		{id::unimplemented_virtual_method, "42run : An virtual method is not implemented"},
		{id::GLFW,                         "42run, Engine, Core : GLFW error"},
		{id::GLAD,                         "42run, Engine, Core : GLAD error"},
		{id::VAO_type,                     "42run, Engine, VAO : Bad data type"},
		{id::VBO_resize_more_than_one,     "42run, Engine, VBO : Shouldn't resize VBO more than once"},
		{id::VBO_static,                   "42run, Engine, VBO : Shouldn't rewrite static buffer"},
		{id::shader_reading,               "42run, Engine, Shader : Can't read source file"},
		{id::shader_compilation,           "42run, Engine, Shader : Can't compile shader"},
		{id::uniform_creation,             "42run, Engine, Uniform : Can't create uniform"},
		{id::uniform_type,                 "42run, Engine, Uniform : Bad uniform type"},
		{id::program_compilation,          "42run, Engine, Program : Can't compile program"}
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