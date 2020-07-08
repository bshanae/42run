#pragma once

#include "game/namespace.h"

#include "game/renderer/renderer.h"
#include "game/character/character.h"
#include "game/room/room.h"
#include "game/obstacle/chair.h"

class							game::manager :
									public global<game::manager>,
									public game_object::game_object
{
public :
								manager();
								~manager() override = default;

private :

	void						initializer(std::shared_ptr<game::manager> pointer) override
	{
		pointer->start();
	}

	shared<room>				room;
	shared<character>			character;

	void						update() override;

	shared<frame::frame>		frame_for_score;
	shared<frame::frame>		frame_for_health;

	shared<font::font>			font;

	shared<label::label>		score;
	shared<icon::icon>			circles[3];

	void						show_health();
	void						show_game_over();

	float						row_value = settings().initial_row_value;
	float						row_value_factor = 1.f;

	float						total_row_value = 0.f;
};
