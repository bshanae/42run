#include "instance.h"

using namespace		engine;

void				model::instance::scale(float value)
{
	scaling = glm::scale(vec3(value));
}

void				model::instance::translate(vec3 value)
{
	translation = glm::translate(value);
}

void				model::instance::rotate(vec3 angles)
{
	angles.x = glm::radians(angles.x);
	angles.y = glm::radians(angles.y);
	angles.z = glm::radians(angles.z);

	rotation = glm::eulerAngleYXZ(angles.y, angles.x, angles.z);
}