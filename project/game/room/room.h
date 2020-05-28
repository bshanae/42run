#pragma once

#include "game/namespace.h"

class						game::room
{
	friend class			manager;

public :

	static inline path		path;

							room();
							~room() = default;
private :

	model::model::ptr		model;
	model::instance::ptr	instances[2];
//	model::group::ptr		group[2];
};


