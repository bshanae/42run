#pragma once

#include <unordered_map>
#include <iostream>

namespace									common
{
	namespace								warning
	{}
}

namespace									common::warning
{
	enum class								id
	{
		model_loader_no_bone,
		model_loader_no_animation
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::model_loader_no_bone,			"Engine, Model, Loader : Bone not found"},
		{id::model_loader_no_animation,		"Engine, Model, Loader : Animation not found"}
	};

	inline void 							raise(id id)
	{
		auto								iterator = messages.find(id);

		std::cerr << "42run Warning";
		if (iterator != messages.end())
			std::cerr << " : " << iterator->second;
		std::cerr << std::endl;
	}
};