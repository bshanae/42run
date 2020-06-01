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
		model_material_property_error,
		model_bone_not_found,
		model_animation_not_found,
		model_bone_without_animation,
		model_is_not_analyzed,
		model_is_not_centered,
		renderer_no_space_for_light
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::model_bone_not_found,			"Engine, Model, Loader : Bone not found"},
		{id::model_animation_not_found,		"Engine, Model, Loader : Animation not found"},
		{id::model_bone_without_animation,	"Engine, Model, Loader : Bone does't have animation"},
		{id::model_is_not_analyzed,			"Engine, Model, Model : Object is not analyzed"},
		{id::model_is_not_centered,			"Engine, Model, Model : Object is not centered"},
		{id::renderer_no_space_for_light,	"Engine, Renderer : Lights data is full"}
	};

	inline bool								ignore = false;

	inline void 							raise(id id)
	{
		auto								iterator = messages.find(id);

		if (ignore)
			return ;
		std::cerr << "42run Warning";
		if (iterator != messages.end())
			std::cerr << " : " << iterator->second;
		std::cerr << std::endl;
	}
};