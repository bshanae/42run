#pragma once

#include "engine/namespace.h"

class						engine::interface::function
{
public :

							function() = default;
	virtual					~function() = default;

	template				<typename function_type, typename ...args_type>
	explicit				function(function_type function, args_type ...args)
	{
		object = static_cast<const std::function<void()>>(std::bind(function, args...));
	}

	explicit				function(const function &that) :
							object(that.object)
							{}

	void					operator () () const
	{
		object();
	}

							operator bool () const
	{
		return (object.operator bool ());
	}

private :

	std::function<void()>	object = std::function<void()>();
};


