#pragma once

#include "engine/namespace.h"

template					<
    							typename enum_type,
    							typename underlying_type = typename std::underlying_type<enum_type>::type
    						>
class						engine::abstract::bitflag_wrapper
{
public:
							bitflag_wrapper() = default;
							~bitflag_wrapper() = default;

							bitflag_wrapper(enum_type flag) : data(static_cast<underlying_type>(flag))
							{}

	template				<typename ...args_type>
							bitflag_wrapper(args_type ...args)
	{
		data = (... | static_cast<underlying_type>(args));
	}

							bitflag_wrapper(const bitflag_wrapper &original) : data(original.data)
							{}

	bitflag_wrapper			&operator |= (enum_type value)
	{
		data |= static_cast<underlying_type>(value);
		return (*this);
	}

	bitflag_wrapper			operator | (enum_type value) const
	{
		bitflag_wrapper		result(*this);

		result |= value;
		return (result);
	}

	bitflag_wrapper			operator | (const bitflag_wrapper &that) const
	{
		bitflag_wrapper	result;

		result.data = this->data | that.data;
		return (result);
	}

	bitflag_wrapper			&operator &= (enum_type mask)
	{
		data &= static_cast<underlying_type>(mask);

		return (*this);
	}

	bitflag_wrapper			operator & (enum_type mask) const
	{
		bitflag_wrapper		result(*this);

		result &= mask;
		return (result);
	}

	bitflag_wrapper			operator ~ () const
	{
		bitflag_wrapper		result(*this);

		result.data = ~result.data;
		return (result);
	}

	explicit				operator bool () const
	{
		return (data != 0);
	}

	bool					does_intersect(enum_type value) const
	{
		return ((data & static_cast<underlying_type>(value)) == static_cast<underlying_type>(value));
	}

	bool					does_intersect(bitflag_wrapper wrapper) const
	{
		return ((data & static_cast<underlying_type>(wrapper.data)) != 0);
	}

	bool					does_contain(bitflag_wrapper wrapper) const
	{
		return ((data & static_cast<underlying_type>(wrapper.data)) == static_cast<underlying_type>(wrapper.data));
	}

protected:

	underlying_type			data = 0;
};