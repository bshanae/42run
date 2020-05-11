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
		model_bone_not_found,
		model_animation_not_found,
		model_bone_without_animation
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::model_bone_not_found,			"Engine, Model, Loader : Bone not found"},
		{id::model_animation_not_found,		"Engine, Model, Loader : Animation not found"},
		{id::model_bone_without_animation,	"Engine, Model, Loader : Bone does't have animation"}
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