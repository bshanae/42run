#pragma once

#include "game/namespace.h"

#include "game/obstacle/chair.h"
#include "game/character/character.h"

class									game::room : public engine::game_object
{
	friend class						manager;

public :
										room();
										~room() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(room)

private :

	void								update() override;

	void								build_models();
	void								build_main_instances();
	void								build_unique_groups();

	void								prepare_offset();
	void								offset_groups();

	struct
	{
		model::model::ptr				room;
		model::model::ptr				chair;
		model::model::ptr				mac;
		model::model::ptr				keyboard;
	}									models;

//										Number of rows (groups)
	static constexpr int				number_of_rows = 10;
	static constexpr int				number_of_accessories = 8;

	struct
	{
		model::instance::ptr			room;
		model::instance::ptr			chair[number_of_accessories];
		model::instance::ptr			mac[number_of_accessories];
		model::instance::ptr			keyboard[number_of_accessories];
	}									instances[number_of_rows];

	struct								row
	{
										row(const model::group::ptr &group) :
											group(group)
										{}

		void							move(const vec3 &value);

		void							link_obstacle(const obstacle::obstacle::ptr &obstacle);
		void							unlink_obstacle();

		bool							does_intersects(const float_range &character_range) const;

		[[nodiscard]] model::group::ptr	read_group() const;

		[[nodiscard]] line_wrapper		blocked_lines() const;
		[[nodiscard]] state_wrapper		blocked_states() const;

	private :

		model::group::ptr				group;
		obstacle::obstacle::ptr			obstacle;

		bool							is_hollow = false;
	};

	deque<row>							rows;

//										Distance between neighbor rows, set in prepare_offset method
	static inline vec3					row_offset = vec3(0.f);
//										Length of one row, described in common::range, used for collision detection
	static inline float_range			row_range = {0.f, 0.f};

//										Movement speed
	static constexpr float				speed = 1.8f;

	struct
	{
//										Distance between neighbor accessories
		const vec3						little = vec3(8, 0, 0);
//										Distance between neighbor tables
		const vec3						big = vec3(30, 0, 0);
	}									intervals;

//										Distance to other side of table
	struct
	{
		const vec3						chair = vec3(0, 0, -12);
		const vec3						mac = vec3(0, 0, 3);
		const vec3						keyboard = vec3(0, 0, -1.5);
	}									jumps;

//										Used for randomizing
	struct
	{
		const vec3_range				chair = {vec3(-1, 0, -1), vec3(1, 0, 1)};
		const vec3_range				keyboard = {vec3(), vec3(0.5, 0, 0.5)};
	}									translation_ranges;

//										Used for randomizing
	struct
	{
		const vec3_range				chair = {vec3(0, -30, 0), vec3(0, 30, 0)};
		const vec3_range				keyboard = {vec3(0, -5, 0), vec3(0, 5, 0)};
	}									rotation_ranges;

//										Obstacles
	void								spawn_chair();

	static inline int_range				dangerous_rows_for_character = int_range(0, 2);
};


