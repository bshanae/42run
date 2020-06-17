#pragma once

#include "engine/namespace.h"

template				<
    						typename enum_type,
    						typename underlying_type = typename std::underlying_type<enum_type>::type
    					>
class					engine::abstract::bitflags
{
public:

						bitflags() : data(0)
						{}
						bitflags(enum_type flag) : data(static_cast<underlying_type>(flag))
						{}
						bitflags(const bitflags &original) : data(original.data)
						{}

	bitflags			&operator |= (enum_type value)
	{
		data |= static_cast<underlying_type>(value);
		return (*this);
	}

	bitflags			operator | (enum_type value)
	{
		bitflags	result(*this);

		result |= value;
		return (result);
	}

	bitflags			&operator &= (enum_type mask)
	{
		data &= static_cast<underlying_type>(mask);
		return (*this);
	}

	bitflags			operator & (enum_type mask)
	{
		bitflags		result(*this);

		result &= mask;
		return (result);
	}

	bitflags			operator ~ ()
	{
		bitflags		result(*this);

		result.data = ~result.data;
		return (result);
	}

	explicit operator	bool()
	{
		return (data != 0);
	}

protected:
	underlying_type		data;
};