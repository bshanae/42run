#pragma once

#include "game/namespace.h"

class						game::character
{
	friend class			manager;

public :

	static inline path		path;

							character();
							~character() = default;
private :

	model::model::ptr		model;
	model::instance::ptr	instance;
};


