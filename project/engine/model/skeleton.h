#pragma once

#include "engine/namespace.h"

#include "engine/model/animation.h"
#include "engine/model/bone.h"

class						engine::model::skeleton
{
	friend class			engine::core;
	friend class 			engine::model::model;
	friend class 			engine::model::reader;

public  :

	static constexpr int	bones_limit = SHARED_BONES_IN_SKELETON;

	explicit				skeleton(const vector<shared<bone>> &bones) :
								bones(bones)
							{}
							~skeleton() = default;

	void					animate(const class animation &animation);

private :

	void 					update();

	vector<shared<bone>>	bones;
	optional<animation>		animation;

	float					time = 0.f;
};