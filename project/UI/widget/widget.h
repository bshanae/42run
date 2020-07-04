#pragma once

#include "UI/namespace.h"

class							UI::widget : public engine::game_object::game_object
{
public :

	template					<typename renderer_type>
								widget(tag<renderer_type> tag) : game_object(tag)
								{}
								~widget() override = default;

	void						set_background();
	void						set_border();

protected :

	void						set_texture(unique<model::texture> &texture);

	shared<model::instance>		instance;

private :

	shared<model::model>		model;
};


