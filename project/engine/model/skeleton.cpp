#include "skeleton.h"

#include "engine/core/core.h"

using namespace		engine;

void				model::skeleton::animate(const class animation &animation)
{
	this->animation.emplace(animation);
}

void 				model::skeleton::update()
{
	if (not animation)
		return ;

	time += animation->speed * engine::core::time_delta(true);

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