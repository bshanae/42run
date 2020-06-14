#include "group.h"

using namespace		engine;

void				model::group::scale(float value)
{
	scaling = glm::scale(vec3(value));
}

void				model::group::translate(vec3 value)
{
	translation = glm::translate(value);
}

void				model::group::rotate(vec3 angles)
{
	angles.x = radians(angles.x);
	angles.y = radians(angles.y);
	angles.z = radians(angles.z);

	rotation = glm::eulerAngleYXZ(angles.y, angles.x, angles.z);
}