#pragma once

#include "engine/namespace.h"

#include "engine/interface/function.h"

class				engine::interface::timer
{
public :
					timer() = default;
					~timer() = default;

	explicit		timer(float value) :
					total(value)
					{}

	template		<typename ...args_type>
	explicit		timer(float value, args_type ...args) :
					total(value),
					function(args...)
					{}

	void 			execute()
	{
		left = total;
		last = glfwGetTime();
	}

	void 			update()
	{
		if (left >= 0.f)
		{
			auto	current = glfwGetTime();

			left -= current - last;
			last = current;

			if (function and has_finished())
				function();
		}
	}

	bool			has_finished() const
	{
		return (left <= 0.f);
	}

private :

	float			total = std::numeric_limits<float>::infinity();

	float			last = 0.f;
	float			left = 0.f;

	function		function;
};