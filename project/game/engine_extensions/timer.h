#pragma once

#include "game/namespace.h"

class				game::engine_extensions::timer : public engine::interface::timer
{
public :

	enum class 		interpolation_method
	{
		linear
	};

					timer() = default;
					~timer() override = default;

					timer(float start, float end, float duration) :
						engine::interface::timer(duration),
						start(start),
						end(end)
					{}

					timer(const float_range &range, float duration) :
						engine::interface::timer(duration),
						start(range.lower),
						end(range.higher)
					{}

	void 			execute() override
	{
		value = start;
		engine::interface::timer::execute();
	}

	void 			update() override
	{
		engine::interface::timer::update();
		value = start + time_passed() * (end - start);
	}

	[[nodiscard]]
	float			get_value() const
	{
		return (value);
	}

private :

	float			start = 0;
	float			end = 0;

	float			value = 0;
};