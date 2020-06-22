#pragma once

#include "game/namespace.h"

#include "game/obstacle/chair.h"

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

	model::group::ptr					groups[number_of_rows];
	deque<model::group::ptr>			groups_in_order;

//										Distance between neighbor rows
	vec3								row_offset = vec3(0.f);

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

//										Obstacle
	class								obstacle_link
	{
	public :
										obstacle_link
										(
											const obstacle::obstacle::ptr &obstacle,
											const model::group::ptr &row
										) :
											obstacle(obstacle),
											row(row)
		{
			obstacle->enable(false);
		}

	IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(obstacle_link)

		void							move_to(const vec3 &row_position)
		{
			obstacle->instance->edit_translation(2, row_position.z);
			obstacle->does_trigger_collision = true;
			obstacle->enable(true);
		}

		const obstacle::obstacle::ptr	obstacle;
		const model::group::ptr			row;
	};

	deque<obstacle_link>				obstacle_links;

	void								spawn_chair()
	{
		auto 							random_int = random(int_range(0, 2));
		enum line						random_line;

		switch (random_int)
		{
			case 0 :
				random_line = line::left;
				break ;

			case 1 :
				random_line = line::middle;
				break ;

			default :
				random_line = line::right;
				break ;
		}

		obstacle::chair::ptr 			chair;

		chair = scene::scene::game_object<obstacle::chair>(random_line);
		push_obstacle(static_pointer_cast<obstacle::obstacle>(chair));
	}

	void								push_obstacle(const obstacle::obstacle::ptr &obstacle);
	void								pop_obstacle(const model::group::ptr &row);
};


