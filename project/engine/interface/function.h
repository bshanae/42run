#pragma once

#include "engine/namespace.h"

class						engine::interface::function
{
public :

	template				<typename function_type, typename ...args_type>
	explicit				function(function_type function, args_type ...args)
	{
		object = static_cast<const std::function<void()>>(std::bind(function, args...));
	}
	virtual					~function() = default;

	void					operator () () const
	{
		object();
	}

private :

	std::function<void()>	object;
};


