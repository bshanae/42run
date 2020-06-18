#pragma once

#include "engine/namespace.h"
#include "engine/interface/function.h"
#include "engine/interface/event.h"

class					engine::interface::callback final : public engine::interface::function
{
	friend class 		engine::core;

public :

						callback() = default;
						~callback() override = default;

	template			<typename... args_type>
	explicit			callback(event::type type, args_type ...args) :
						function(args...),
						type(type)
						{}
private :

	event::type			type = event::type::none;
};


