#pragma once

#include "game/namespace.h"

#include "game/engine_extensions/timer.h"
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
	shared<engine_extensions::instance>	instance;

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

	engine_extensions::timer			timer_for_obstacle;
	engine_extensions::timer			timer_for_protection;

	int									health = 3;
	bool								is_protected = false;

	void								collide_with_obstacle();
	void								collide_with_heal();
	void								collide_with_protection();
};