#pragma once

#include <unordered_map>
#include <iostream>

namespace									common
{
	namespace								error
	{}
}

namespace 									common::error
{
	enum class								id
	{
		unimplemented_virtual_method,
		empty_global_object,
		engine_bad_global_value,
		GLFW_error,
		GLAD_error,
		ASSIMP_error,
		shader_file_error,
		shader_compilation_error,
		uniform_bad_value,
		uniform_bad_type,
		program_compilation_error,
		texture_creation_error,
		texture_bad_format,
		event_bad_type,
		model_too_many_bones,
		light_bad_input,
		scene_bad_game_object_parent,
		scene_game_object_not_found,
		freetype_library_error,
		freetype_face_error,
		freetype_symbol_error,
		room_bad_obstacle_type
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::unimplemented_virtual_method,	"A virtual method is not implemented"},
		{id::empty_global_object,			"A global object is not initialized"},
		{id::engine_bad_global_value,		"Engine : Global struct is not completed"},
		{id::GLFW_error,					"Engine : GLFW error"},
		{id::GLAD_error,					"Engine : GLAD error"},
		{id::ASSIMP_error,					"Engine : ASSIMP error"},
		{id::shader_file_error,				"Engine, Shader : Can't read file"},
		{id::shader_compilation_error,		"Engine, Shader : Can't compile shader"},
		{id::uniform_bad_value,				"Engine, Uniform : Bad uniform value, maybe uniform is not initialized"},
		{id::uniform_bad_type,				"Engine, Uniform : Bad uniform type"},
		{id::program_compilation_error,		"Engine, Program : Can't compile program"},
		{id::texture_creation_error,		"Engine, Texture : Can't create texture"},
		{id::texture_bad_format,			"Engine, Texture : Bad format"},
		{id::event_bad_type,				"Engine, Event : Bad type"},
		{id::model_too_many_bones,			"Engine, Model, Loader : Mesh has too many bones"},
		{id::light_bad_input,				"Engine, Scene, Light : Bad input arguments for constructor"},
		{id::scene_bad_game_object_parent,	"Engine, Scene, Scene : Given type is not derived from game_object"},
		{id::scene_game_object_not_found,	"Engine, Scene, Scene : game_object not found"},
		{id::freetype_library_error,		"UI, Font, FreeType controller : Can't initialize FreeType library"},
		{id::freetype_face_error,			"UI, Font, Font : Can't initialize FreeType face"},
		{id::freetype_symbol_error,			"UI, Font, Font : Can't initialize FreeType symbol"},
		{id::room_bad_obstacle_type,		"Game, Room : Given type is not derived from obstacle"}
	};

	inline void								raise(id id)
	{
		auto								iterator = messages.find(id);

		std::cerr << "42run Error";
		if (iterator != messages.end())
			std::cerr << " : " << iterator->second;
		std::cerr << std::endl;

		std::terminate();
	}
};