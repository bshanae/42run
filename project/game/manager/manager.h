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

	static constexpr float		row_value = 10.f;
	float						total_row_value = 0.f;

	static inline const vec3	main_font_color = vec3(1.f);
	static inline const vec3	bonus_font_color = vec3(0.07f, 0.45f, 1.f);

	engine_extensions::timer	timer_for_font;

	void						display_health();
	void						use_bonus(const shared<bonus::bonus> &bonus);

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
		shared<icon::icon>		blue_circles[3];
		shared<icon::icon>		green_circles[3];
	}							icons;

	struct
	{
		shared<scene::scene>	intro;
		shared<scene::scene>	victory;
		shared<scene::scene>	defeat;
	}							scenes;
};
