#pragma once

#include "UI/namespace.h"

class				UI::frame::renderer : public engine::renderer
{
public :
					renderer() = default;
					~renderer() override = default;
private :

	void			render(const shared<engine::game_object::game_object> &object) const override;
};