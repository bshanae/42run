#pragma once

#include "engine/namespace.h"

#include "engine/abstract/bitflag_wrapper.h"

namespace			engine::model
{
	enum class		flag : uint
	{
		triangulate = 1u << 1u,
		analyze = 1u << 2u,
		center = 1u << 3u
	};

	using			flag_wrapper = engine::abstract::bitflag_wrapper<flag>;
};