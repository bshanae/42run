#pragma once

#include "UI/namespace.h"

class							UI::icon::renderer :
									public engine::renderer
{
public :
								renderer();
								~renderer() = default;
private :

	void						render(const shared<engine::game_object::game_object> &object) const override;
	void						render(const shared<model::instance> &instance) const;

	unique<program::program>	program;

	template					<typename type>
	using						uniform = program::uniform<type>;

	struct
	{
		uniform<int>			texture;
		uniform<mat4>			projection;
		uniform<mat4>			scaling;
		uniform<mat4>			translation;
	}							uniforms;
};


