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
	model::group::ptr		groups[10];
};


