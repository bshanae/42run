#include "skeleton.h"

using namespace		engine;

void				model::skeleton::animate(const class animation &new_animation)
{
	if (animation and new_animation.priority >= animation->priority)
		animation.emplace(new_animation);
	else if (not animation)
		animation.emplace(new_animation);

	time = this->animation->timestamps.begin;
}

void				model::skeleton::reset()
{
	time = 0.f;
	animation.reset();
}

void 				model::skeleton::update()
{
	if (not animation)
		return ;

	time += animation->speed;

	if (time < animation->timestamps.begin)
		time = animation->timestamps.begin;

	if (time > animation->timestamps.end)
	{
		if (animation->loop)
			time = animation->timestamps.begin;
		else
			reset();
	}

	for (auto &bone : bones)
		bone->update_keyframe_transformation(time);
}