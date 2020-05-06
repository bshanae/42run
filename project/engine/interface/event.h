#pragma once

#include "engine/namespace.h"

#include "engine/interface/key.h"

class 				engine::interface::event
{
	friend class 	engine::core;

public :

	enum class		type
	{
		none,
		key_press,
		key_release,
		key_hold
	};

public :
					event() = default;
					~event() = default;

	[[nodiscard]]
	enum key		read_key() const
	{
		switch (type_value)
		{
			case type::key_press :
			case type::key_release :
			case type::key_hold :
				break ;
			default :
				throw (exception::make<exception::id::event_bad_type>());
		}
		return (key_value.value());
	}

private :

	enum type		type_value = type::none;
	optional<key>	key_value;
};
