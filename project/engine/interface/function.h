#pragma once

#include "engine/namespace.h"

class						engine::function
{
public :

	template				<typename function_type, typename ...args_type>
	explicit				function(function_type function, args_type ...args)
	{
		object = std::bind(function, args...);
	}
	virtual					~function() = default;

	void					operator () () const
	{
		object();
	}

private :

	std::function<void()>	object;
};


