#pragma once

#include "engine/namespace.h"

template				<
    						typename enum_type,
    						typename underlying_type = typename std::underlying_type<enum_type>::type
    					>
class					engine::abstract::bitflags_wrapper
{
public:
						bitflags_wrapper() : data(0)
						{}
						bitflags_wrapper(enum_type flag) : data(static_cast<underlying_type>(flag))
						{}
						bitflags_wrapper(const bitflags_wrapper &original) : data(original.data)
						{}

	bitflags_wrapper			&operator |= (enum_type value)
	{
		data |= static_cast<underlying_type>(value);
		return (*this);
	}

	bitflags_wrapper			operator | (enum_type value)
	{
		bitflags_wrapper	result(*this);

		result |= value;
		return (result);
	}

	bitflags_wrapper			&operator &= (enum_type mask)
	{
		data &= static_cast<underlying_type>(mask);
		return (*this);
	}

	bitflags_wrapper			operator & (enum_type mask)
	{
		bitflags_wrapper		result(*this);

		result &= mask;
		return (result);
	}

	bitflags_wrapper			operator ~ ()
	{
		bitflags_wrapper		result(*this);

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