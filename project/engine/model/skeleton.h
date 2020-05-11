#pragma once

#include "engine/namespace.h"

#include "engine/model/animation.h"

class						engine::model::skeleton
{
private :

	friend class 			model;
	friend class 			engine::renderer;

	static constexpr int	bones_limit = 100;

public:
							skeleton(const vector<bone *> &bones) :
							bones(bones)
							{}
							~skeleton() = default;

	void					animate(const class animation &new_animation);
	void					reset();
private :

	void 					update();

	vector<bone *>			bones;
	optional<animation>		animation;

	float					time = 0.f;
};