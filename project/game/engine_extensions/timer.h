#pragma once

#include "game/namespace.h"

class						game::engine_extensions::timer : public engine::interface::timer
{
public :
							timer() = default;
							~timer() override = default;

							timer
							(
								float start,
								float end,
								float duration,
								interpolation_method method = interpolation_method::linear
							) :
								engine::interface::timer(duration),
								interpolation_method(method),
								start(start),
								end(end)
							{}

	void 					update() override
	{
		engine::interface::timer::update();
	}

	[[nodiscard]] float		value() const
	{
		switch (interpolation_method)
		{
			case interpolation_method::linear :
				return (start + (end - start) * time_passed());

			case interpolation_method::cosine :
				return (start + (end - start) * (-cos((float)M_PI * time_passed()) / 2.f + 0.5f));
		}
	}

private :

	interpolation_method	interpolation_method = interpolation_method::linear;

	float					start = 0.f;
	float					end = 0.f;
};