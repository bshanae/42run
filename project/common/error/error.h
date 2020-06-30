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
		GLFW_error,
		GLEW_error,
		ASSIMP_error,
		renderer_not_found,
		shader_file_error,
		shader_compilation_error,
		uniform_bad_value,
		uniform_bad_type,
		program_compilation_error,
		texture_creation_error,
		texture_bad_format,
		event_bad_type,
		model_too_many_bones,
		game_object_bad_logic,
		light_bad_input,
		freetype_library_error,
		freetype_face_error,
		freetype_symbol_error,
		room_bad_obstacle_type
	};

	using									messages_type = const std::unordered_map<id, const char *>;
	messages_type							messages =
	{
		{id::unimplemented_virtual_method,	"A virtual method is not implemented"},
		{id::empty_global_object,         	"A global object is not initialized"},
		{id::GLFW_error,                  	"Engine : GLFW error"},
		{id::GLEW_error,                  	"Engine : GLAD error"},
		{id::ASSIMP_error,                	"Engine : ASSIMP error"},
		{id::renderer_not_found,			"Engine : Renderer not found"},
		{id::shader_file_error,           	"Engine : Can't read fil"},
		{id::shader_compilation_error,    	"Engine : Can't compile shader"},
		{id::uniform_bad_value,           	"Engine : Bad uniform value, maybe uniform is not initialized"},
		{id::uniform_bad_type,            	"Engine : Bad uniform type"},
		{id::program_compilation_error,   	"Engine : Can't compile program"},
		{id::texture_creation_error,      	"Engine : Can't create texture"},
		{id::texture_bad_format,          	"Engine : Bad format of texture"},
		{id::event_bad_type,              	"Engine : Bad type of event"},
		{id::model_too_many_bones,        	"Engine : Mesh has too many bones"},
		{id::game_object_bad_logic,			"Engine : Bad usage of game object"},
		{id::light_bad_input,				"Engine : Bad input arguments for constructor"},
		{id::freetype_library_error,		"UI : Can't initialize FreeType library"},
		{id::freetype_face_error,			"UI : Can't initialize FreeType face"},
		{id::freetype_symbol_error,			"UI : Can't initialize FreeType symbol"},
		{id::room_bad_obstacle_type,		"Game : Given type is not derived from obstacle"}
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