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

	void						update() override;

	bool						is_loaded = false;

	void						load_scene();
	void						unload_scene();
	void						display_health();

	shared<room>				room;
	shared<character>			character;

	struct
	{
		shared<frame::frame>	score;
		shared<frame::frame>	health;
	}							frames;

	struct
	{
		shared<font::font>		intro;
		shared<font::font>		victory;
		shared<font::font>		defeat;
		shared<font::font>		score;
	}							fonts;

	struct
	{
		shared<label::label>	intro;
		shared<label::label>	victory;
		shared<label::label>	defeat;
		shared<label::label>	score;
	}							labels;

	struct
	{
		shared<icon::icon>		circles[3];
	}							icons;

	struct
	{
		shared<scene::scene>	intro;
		shared<scene::scene>	victory;
		shared<scene::scene>	defeat;
	}							scenes;

	float						row_value = settings().initial_row_value;
	float						row_value_factor = 1.f;

	float						total_row_value = 0.f;
};
