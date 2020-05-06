#pragma once

#include "engine/namespace.h"

#include "engine/model/animation.h"

class						engine::model::skeleton
{
private :

	friend class 			model;
	friend class 			engine::renderer;

	static constexpr int	limit_for_bones = 100;

public:
							skeleton(const vector<bone *> &bones) : bones(bones) {}
							~skeleton() = default;

	void					play(class animation *animation, bool reset)
	{
		if (animation and animation->priority >= this->animation->priority)
			this->animation = animation;
		else if (not animation)
			this->animation = animation;

		if (reset)
			time = this->animation->begin_time;
	}

	void					stop()
	{
		time = 0.f;
		animation = nullptr;
	}


private :

	vector<bone *>			bones;
	vector<mat4>			matrices;

	animation				*animation = nullptr;

	float					time = 0.f;
};