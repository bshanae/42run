#pragma once

#include "game/namespace.h"

#include "game/obstacle/chair.h"

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
	vec3						row_offset = vec3(0.f);

//								Movement speed
	static constexpr float		speed = 1.8f;

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

//								Obstacles
	struct
	{
		obstacle::chair::ptr	chair;
	}							obstacles;

	class						obstacle_link
	{
	public :
								obstacle_link
								(
									const obstacle::obstacle::ptr &obstacle,
									int row_index
								) :
									obstacle(obstacle),
									row_index(row_index)
		{
			obstacle->enable(false);
		}

								~obstacle_link()
		{
			obstacle.reset();
#warning "delete game object?"
		}

	IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(obstacle_link)

		void					move_to(const vec3 &row_position)
		{
			vec3				position;

			position = obstacle->instance->translation();
			position.z = row_position.z;

			obstacle->instance->reset_translation();
			obstacle->instance->translate(position);

			obstacle->enable(true);
		}

		[[nodiscard]] auto		read_obstacle() const
		{
			return (obstacle);
		}

		[[nodiscard]] auto		read_row_index() const
		{
			return (row_index);
		}

	private :

		obstacle::obstacle::ptr	obstacle;
		int						row_index;
	};

	list<obstacle_link>			obstacle_links;

	void						link_obstacle_to_row(const obstacle::obstacle::ptr &obstacle, int row_index);
	void						delete_link(int row_index);
};


