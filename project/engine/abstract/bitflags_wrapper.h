#pragma once

#include "engine/namespace.h"

template					<
    							typename enum_type,
    							typename underlying_type = typename std::underlying_type<enum_type>::type
    						>
class						engine::abstract::bitflags_wrapper
{
public:
							bitflags_wrapper() : data(0)
							{}
							bitflags_wrapper(enum_type flag) : data(static_cast<underlying_type>(flag))
							{}
							bitflags_wrapper(const bitflags_wrapper &original) : data(original.data)
							{}

	bitflags_wrapper		&operator |= (enum_type value)
	{
		data |= static_cast<underlying_type>(value);
		return (*this);
	}

	bitflags_wrapper		operator | (enum_type value) const
	{
		bitflags_wrapper	result(*this);

		result |= value;
		return (result);
	}

	bitflags_wrapper		operator | (const bitflags_wrapper &that) const
	{
		bitflags_wrapper	result;

		result.data = this->data | that.data;
		return (result);
	}

	bitflags_wrapper		&operator &= (enum_type mask)
	{
		data &= static_cast<underlying_type>(mask);

		return (*this);
	}

	bitflags_wrapper		operator & (enum_type mask) const
	{
		bitflags_wrapper	result(*this);

		result &= mask;
		return (result);
	}

	bitflags_wrapper		operator ~ () const
	{
		bitflags_wrapper	result(*this);

		result.data = ~result.data;
		return (result);
	}

	explicit				operator bool () const
	{
		return (data != 0);
	}

	bool					has(enum_type value) const
	{
		return ((data & static_cast<underlying_type>(value)) == static_cast<underlying_type>(value));
	}

protected:

	underlying_type			data;
};