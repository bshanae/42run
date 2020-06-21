#pragma once

#include "engine/namespace.h"

#include "engine/model/animation.h"
#include "engine/model/bone.h"

class						engine::model::skeleton
{
public  :

	friend class 			model;
	friend class 			engine::renderer;

	static constexpr int	bones_limit = SHARED_BONES_IN_SKELETON;

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(skeleton)

public:

	explicit				skeleton(const vector<bone::ptr> &bones) :
							bones(bones)
							{}
							~skeleton() = default;

	void					animate(const class animation &animation);

private :

	void 					update();

	vector<bone::ptr>		bones;
	optional<animation>		animation;

	float					time = 0.f;
};