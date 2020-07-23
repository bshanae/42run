#pragma once

#include "engine/namespace.h"

#include "engine/interface/function.h"

class				engine::interface::timer
{
	friend class	engine::core;

public :

	enum class 		state
	{
		waiting,
		running,
		finished
	};

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
			state = state::running;
		}
		else
			warning::raise(warning::id::cant_execute_timer);
	}

	virtual void 	update()
	{
		if (state == state::running)
		{
			auto	current = glfwGetTime();

			left -= current - last;
			last = current;

			if (left <= 0.f)
			{
				state = state::finished;
				left = 0.f;
				if (function)
					function();
			}
		}
	}

	[[nodiscard]]
	state			get_state() const
	{
		return (state);
	}

	float			time_passed() const
	{
		if (not total)
			return (0.f);
		if (left < 0.f)
			return (1.f);
		return ((*total - left) / *total);
	}

private :

	state			state = state::waiting;

	optional<float>	total;

	float			last = 0.f;
	float			left = 0.f;

	function		function;
};