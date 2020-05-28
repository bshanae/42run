#pragma once

#include "engine/namespace.h"

#include "engine/model/animation.h"
#include "engine/model/bone.h"

class						engine::model::skeleton
{
public  :

	friend class 			model;
	friend class 			engine::renderer;

	static constexpr int	bones_limit = 100;

IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(skeleton)

public:
							skeleton(const vector<bone::ptr> &bones) :
							bones(bones)
							{}
							~skeleton() = default;

	void					animate(const class animation &new_animation);
	void					reset();
private :

	void 					update();

	vector<bone::ptr>		bones;
	optional<animation>		animation;

	float					time = 0.f;
};