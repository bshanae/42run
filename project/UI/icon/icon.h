#pragma once

#include "UI/namespace.h"

#include "UI/widget/widget.h"

class					UI::icon::icon : public UI::widget
{
	friend class		UI::icon::renderer;

public :

	explicit			icon(const vec2 &position, const path &source);
						~icon() override = default;

	void				reposition(const vec2 &position);
};


