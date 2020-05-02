#pragma once

#include "engine/namespace.h"
#include "engine/interface/function.h"
#include "engine/interface/event.h"

class					engine::callback final : public engine::function
{
	friend class 		core;
public :

	template			<typename... args_type>
						callback(event::type type, args_type ...args) :
						function(args...),
						type(type)
						{}
						~callback() override = default;
private :

	const event::type	type;
};


