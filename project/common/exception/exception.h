#pragma once

#include "common/namespace.h"

class									common::exception
{
public :

	enum class							id
	{
		standard,
		GLFW_error,
		GLEW_error
	};

	const std::map<id, const char *>	messages =
	{
		{id::standard,					"42run : Standard exception"},
		{id::GLFW_error,				"42run, Engine, Core : GLFW error"},
		{id::GLEW_error,				"42run, Engine, Core : GLEW error"},
	};

private :
										exception() = default;
										~exception() = default;

	static exception					&instance()
	{
		static exception				exception;

		return (exception);
	}

	template							<enum id id>
	class 								object : public std::exception
	{
		friend class 					common::exception;

	private :
		explicit 						object(const char *message) :
										message(message) {}
	public :
										~object() override = default;

		[[nodiscard]] const char		*what() const noexcept override
		{
			return (message);
		}

	private :

		const char 						*message;
	};

public :

	template							<enum id id>
	static auto 						make_object()
	{
		auto 							&instance = exception::instance();
		auto							message = instance.messages.find(id);

		assert(message != instance.messages.end());
		return (object<id>(message->second));
	}
};