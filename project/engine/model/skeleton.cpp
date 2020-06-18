#include "skeleton.h"

using namespace		engine;

void				model::skeleton::animate(const class animation &animation)
{
	this->animation.emplace(animation);
}

void 				model::skeleton::update()
{
	if (not is_animation_playing())
		return ;

	time += animation->speed;

	if (time < animation->timestamps.begin)
		time = animation->timestamps.begin;

	if (time > animation->timestamps.end)
	{
		animation.reset();
		time = 0.f;
	}

	for (auto &bone : bones)
		bone->update_keyframe_transformation(time);
}