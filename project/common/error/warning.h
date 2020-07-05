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
//		Engine
		model_bone_not_found,
		model_animation_not_found,
		model_bone_without_animation,
		model_is_not_analyzed,
		renderer_no_space_for_light,
		game_object_without_renderer,
//		UI
		font_symbol_not_found,
		object_without_texture,
		object_improper_type,
//		Game
		unexpected_health_value
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
//		Engine
		{id::model_bone_not_found,			"Engine : Bone not found"},
		{id::model_animation_not_found,		"Engine : Animation not found"},
		{id::model_bone_without_animation,	"Engine : Bone does't have animation"},
		{id::model_is_not_analyzed,			"Engine : Object is not analyzed"},
		{id::renderer_no_space_for_light,	"Engine : Lights data is full"},
		{id::game_object_without_renderer,	"Engine : Game object doesn't have renderer"},
//		UI
		{id::font_symbol_not_found,			"UI : Can't find symbol"},
		{id::object_without_texture,		"UI : Object assumed to be rectangle, doesn't have texture"},
		{id::object_improper_type,			"UI : Object has improper type"},
//		Game
		{id::unexpected_health_value,		"Game : Unexpected health value"}
	};

	inline bool								is_muted = false;
	inline bool								is_critical = false;

	inline void 							raise(id id)
	{
		auto								iterator = messages.find(id);

		if (is_muted)
			return ;

		std::cerr << "42run Warning";
		if (iterator != messages.end())
			std::cerr << " : " << iterator->second;
		std::cerr << std::endl;

		if (is_critical)
			std::terminate();
	}
};