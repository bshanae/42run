#pragma once

#include "engine/namespace.h"
#include "engine/functor/functor.h"
#include "engine/event/event.h"

class					engine::callback final : public engine::function
{
public :

	template			<typename... args_type>
						callback(event::type type, args_type ...args) :
						function(args...), type(type) {}
						~callback() override = default;

	void				operator () () const override
	{
		if (not is_blocked() and this->type == type)
			functor::run();
	}

private :

	const event::type	type;
};


