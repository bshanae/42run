#pragma once

#include "game/namespace.h"

class							game::room
{
	friend class				manager;

public :
								room();
								~room() = default;
private :

	struct
	{
		model::model::ptr		room;
		model::model::ptr		chair;
		model::model::ptr		mac;
		model::model::ptr		keyboard;
	}							models;

	struct
	{
		model::instance::ptr	room;
		model::instance::ptr	chair[8];
		model::instance::ptr	mac[8];
		model::instance::ptr	keyboard[8];
	}							instances;

	model::group::ptr			groups[10];

	struct
	{
		const vec3				little = vec3(8, 0, 0);
		const vec3				big = vec3(30, 0, 0);
	}							intervals;

	struct
	{
		const vec3				chair = vec3(0, 0, -12);
		const vec3				mac = vec3(0, 0, 3);
		const vec3				keyboard = vec3(0, 0, -1.5);
	}							jumps;

	struct
	{
		const vec3_range		chair = {vec3(-1, 0, -1), vec3(1, 0, 1)};
		const vec3_range		keyboard = {vec3(), vec3(0.5, 0, 0.5)};
	}							translation_ranges;

	struct
	{
		const vec3_range		chair = {vec3(0, -30, 0), vec3(0, 30, 0)};
		const vec3_range		keyboard = {vec3(0, -5, 0), vec3(0, 5, 0)};
	}							rotation_ranges;
};


