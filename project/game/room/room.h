#pragma once

#include "game/namespace.h"

class							game::room : public engine::game_object
{
	friend class				manager;

public :
								room();
								~room() override = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(room)

private :

	void						update() override;

	void						build_models();
	void						build_main_instances();
	void						build_unique_groups();
	void						offset_groups();
	void						set_targets();

	struct
	{
		model::model::ptr		room;
		model::model::ptr		chair;
		model::model::ptr		mac;
		model::model::ptr		keyboard;
	}							models;

//								Number of rows (groups)
	static constexpr int		number_of_rows = 10;
	static constexpr int		number_of_accessories = 8;

	struct
	{
		model::instance::ptr	room;
		model::instance::ptr	chair[number_of_accessories];
		model::instance::ptr	mac[number_of_accessories];
		model::instance::ptr	keyboard[number_of_accessories];
	}							instances[number_of_rows];

	model::group::ptr			groups[number_of_rows];

//								Distance between neighbor rows
	vec3						row_offset;

	struct
	{
//								Distance between neighbor accessories
		const vec3				little = vec3(8, 0, 0);
//								Distance between neighbor tables
		const vec3				big = vec3(30, 0, 0);
	}							intervals;

//								Distance to other side of table
	struct
	{
		const vec3				chair = vec3(0, 0, -12);
		const vec3				mac = vec3(0, 0, 3);
		const vec3				keyboard = vec3(0, 0, -1.5);
	}							jumps;

//								Used for randomizing
	struct
	{
		const vec3_range		chair = {vec3(-1, 0, -1), vec3(1, 0, 1)};
		const vec3_range		keyboard = {vec3(), vec3(0.5, 0, 0.5)};
	}							translation_ranges;

//								Used for randomizing
	struct
	{
		const vec3_range		chair = {vec3(0, -30, 0), vec3(0, 30, 0)};
		const vec3_range		keyboard = {vec3(0, -5, 0), vec3(0, 5, 0)};
	}							rotation_ranges;
};


