#pragma once

#include "game/namespace.h"

#include "game/character/character.h"
#include "game/obstacle/obstacle.h"
#include "game/bonus/bonus.h"

class										game::room : public engine::game_object::game_object
{
	friend class							manager;

public :
											room();
											~room() override = default;
private :

	void									update() override;

	void									build_models();
	void									build_instances();
	void									build_groups();

	void									prepare_offset();
	void									offset_groups();

	struct
	{
		shared<model::model>				room;
		shared<model::model>				chair;
		shared<model::model>				mac;
		shared<model::model>				keyboard;
	}										models;

//											Number of rows (groups)
	static constexpr int					number_of_rows = 10;
	static constexpr int					number_of_accessories = 8;

	struct
	{
		shared<model_with_mods::instance>	room;
		shared<model_with_mods::instance>	chair[number_of_accessories];
		shared<model_with_mods::instance>	mac[number_of_accessories];
		shared<model_with_mods::instance>	keyboard[number_of_accessories];
	}										instances[number_of_rows];

	struct									row
	{
		explicit							row(const shared<model_with_mods::group> &group) :
												group(group)
											{}

		void								move(const vec3 &value);

		void								make_hollow(bool state);
		void 								make_hollow_temporarily(bool state);

		void								link_obstacle(const shared<obstacle::obstacle> &obstacle);
		void								link_bonus(const shared<bonus::bonus> &bonus);

		[[nodiscard]]
		shared<model_with_mods::group>		read_group() const;

		[[nodiscard]]
		bool								does_collide(const float_range &character_range) const;
		[[nodiscard]]
		bool								does_collide_with_obstacle(line character_line, const state_wrapper &character_state) const;
		[[nodiscard]]
		pair<bool, shared<bonus::bonus>>	does_collide_with_bonus(line character_line, const state_wrapper &character_state) const;

		bool								is_line_free(line_wrapper line);

	private :

		static inline const line_wrapper	lines_blocked_by_hollow_row = {line::left, line::middle, line::right};
		static inline const state_wrapper 	states_blocked_by_hollow_row = state::running;

		shared<model_with_mods::group>		group;

		shared<obstacle::obstacle>			obstacle;
		shared<bonus::bonus>				bonus;

		bool								is_hollow = false;

		void								make_hollow_internal(bool state);
	};

	deque<shared<row>>						rows;
	int										rows_swap_counter = 0;

//											Distance between neighbor rows, set in prepare_offset method
	static inline vec3						row_offset = vec3(0.f);
//											Length of one row, described in common::range, used for collision detection
	static inline float_range				row_range = {0.f, 0.f};

//											Movement speed
	float									speed = settings().initial_room_speed;
	float									speed_factor = 1.f;

	struct
	{
//											Distance between neighbor accessories
		const vec3							little = vec3(8, 0, 0);
//											Distance between neighbor tables
		const vec3							big = vec3(30, 0, 0);
	}										intervals;

//											Distance to other side of table
	struct
	{
		const vec3							chair = vec3(0, 0, -12);
		const vec3							mac = vec3(0, 0, 3);
		const vec3							keyboard = vec3(0, 0, -1.5);
	}										jumps;

//											Used for randomizing
	struct
	{
		const vec3_range					chair = {vec3(-1, 0, -1), vec3(1, 0, 1)};
		const vec3_range					keyboard = {vec3(), vec3(0.5, 0, 0.5)};
	}										translation_ranges;

//											Used for randomizing
	struct
	{
		const vec3_range					chair = {vec3(0, -30, 0), vec3(0, 30, 0)};
		const vec3_range					keyboard = {vec3(0, -5, 0), vec3(0, 5, 0)};
	}										rotation_ranges;

//											Obstacles
	void									spawn_chair();
	void									spawn_hollow_row();

//											Bonuses
	void									spawn_coin();
	void									spawn_heal();
	void									spawn_protection();
};


