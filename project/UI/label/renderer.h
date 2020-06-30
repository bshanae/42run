#pragma once

#include "UI/namespace.h"

#include "UI/font/reader.h"

class							UI::label::renderer :
									public engine::renderer,
									public UI::font::reader
{
public :
								renderer() = default;
								~renderer() override = default;
private :

	void						render(const shared<engine::game_object::game_object> &object) const override;

	unique<program::program>	program;

	template					<typename type>
	using						uniform = program::uniform<type>;
};


