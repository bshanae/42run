#pragma once

#include "engine/namespace.h"

#include "engine/interface/function.h"

class				engine::interface::timer
{
public :
					timer() = default;
	virtual			~timer() = default;

	explicit		timer(float value) :
						total(value)
					{}

	template		<typename ...args_type>
	explicit		timer(float value, args_type ...args) :
					total(value),
					function(args...)
					{}

	virtual void	execute()
	{
		if (total)
		{
			left = *total;
			last = glfwGetTime();
		}
		else
			warning::raise(warning::id::cant_execute_timer);
	}

	virtual void 	update()
	{
		if (left >= 0.f)
		{
			auto	current = glfwGetTime();

			left -= current - last;
			last = current;

			if (function and has_finished())
				function();
		}

		cerr << "timer : left = " << left << endl;
	}

	[[nodiscard]]
	bool			is_running() const
	{
		return (left > 0.f);
	}

	[[nodiscard]]
	bool			has_finished() const
	{
		return (total and left <= 0.f);
	}

	float			time_passed()
	{
		if (not total)
			return (0.f);
		if (left < 0.f)
			return (1.f);
		return ((*total - left) / *total);
	}

private :

	optional<float>	total;

	float			last = 0.f;
	float			left = 0.f;

	function		function;
};