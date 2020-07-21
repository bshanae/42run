#pragma once

#include "game/namespace.h"

#include "game/obstacle/obstacle.h"

class									game::character : public engine::game_object::game_object
{
	friend class						manager;

public :
										character();
										~character() override = default;
private :

	void								update() override;

	float_range							calculate_range() const;

	void								callback_functor();
	interface::callback					callback;

	shared<model::model>				model;
	shared<model_with_mods::instance>	instance;

	static constexpr float				size = 5.f;

	struct
	{
		model::animation				run;
		model::animation				jump;
	}									animations;

//										Speed of changing row action
	float								speed = settings().initial_character_speed;
	float								speed_factor = 1.f;

	line								current_line = line::middle;
	enum state							current_state = state::running;

	void								update_state();

	const vec3							middle_position = vec3(0.f);
	const vec3							left_position = middle_position - vec3(constants::distance_between_lines, 0, 0);
	const vec3							right_position = middle_position + vec3(constants::distance_between_lines, 0, 0);

	const vec3							&position_for_line(enum line line);

	bool								try_go_left(enum line &line);
	bool								try_go_right(enum line &line);

	vec3 								current_position = middle_position;
	vec3								target_position = middle_position;

	interface::timer					timer;
	int									health = 3;
	float								color_mix_value;

	void								get_hit();
	void								use_bonus(const shared<bonus::bonus> &bonus);
};


