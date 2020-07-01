#pragma once

#include "UI/namespace.h"

#include "UI/rectangle/renderer.h"

class						UI::rectangle::rectangle : public engine::game_object::game_object
{
public :
							rectangle(unique<model::texture> &texture);
							~rectangle() override = default;

	shared<model::instance>	instance;

private :

	shared<model::model>	model;
};


