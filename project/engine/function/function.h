#pragma once

#include "engine/namespace.h"

class						engine::function
{
public :

	template				<typename function_type, typename... args_type >
	explicit				function(function_type function, args_type ...args)
	{
		this->function = bind(function, args...);
	}
	virtual					~function() = default;

	virtual void			operator () const
	{
		if (not block_value)
			function();
	}

	void					block(bool state)
	{
		block_value = state;
	}

	[[nodiscard]]
	bool					is_blocked() const
	{
		return (block_value);
	}

private :

	std::function<void()>	function;
	bool					block_value = false;
};


