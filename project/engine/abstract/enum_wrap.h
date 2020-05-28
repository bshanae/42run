#pragma once

#include "engine/namespace.h"

template				<
    						typename enum_type,
    						typename underlying_type = typename std::underlying_type<enum_type>::type
    					>
class					engine::abstract::enum_wrap
{
public:

						enum_wrap() : data(0)
						{}
						enum_wrap(enum_type flag) : data(static_cast<underlying_type>(flag))
						{}
						enum_wrap(const enum_wrap &original) : data(original.data)
						{}

	enum_wrap			&operator |= (enum_type value)
	{
		data |= static_cast<underlying_type>(value);
		return (*this);
	}

	enum_wrap			operator | (enum_type value)
	{
		enum_wrap	result(*this);

		result |= value;
		return (result);
	}

	enum_wrap			&operator &= (enum_type mask)
	{
		data &= static_cast<underlying_type>(mask);
		return (*this);
	}

	enum_wrap			operator & (enum_type mask)
	{
		enum_wrap		result(*this);

		result &= mask;
		return (result);
	}

	enum_wrap			operator ~ ()
	{
		enum_wrap		result(*this);

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