#pragma once

#include "UI/namespace.h"

#include "UI/rectangle/renderer.h"

class						UI::rectangle::rectangle :
								public engine::game_object::game_object
{
protected :

	template				<typename renderer_type = UI::rectangle::renderer>
							rectangle(tag<renderer_type> tag = common::tag<UI::rectangle::renderer>()) :
								game_object(tag)
							{}
							~rectangle() override = default;

	void					build(const vec3 &color);
	void					build(unique<model::texture> &texture);

	shared<model::instance>	instance;

private :

	void					build_model(unique<model::material> &material);

	shared<model::model>	model;
};


