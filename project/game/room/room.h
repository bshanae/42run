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
		model::instance::ptr	chair;
		model::instance::ptr	mac;
		model::instance::ptr	keyboard;
	}							instances;

	model::group::ptr			groups[10];
};


