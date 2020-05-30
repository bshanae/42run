#include "instance.h"

using namespace		engine;

void				model::instance::scale(float value, bool reset)
{
	if (reset)
		scaling = glm::scale(vec3(value));
	else
		scaling *= glm::scale(vec3(value));
}

void				model::instance::translate(vec3 value, bool reset)
{
	if (reset)
		translation = glm::translate(value);
	else
		translation *= glm::translate(value);
}

void				model::instance::rotate(vec3 angles, bool reset)
{
	angles.x = glm::radians(angles.x);
	angles.y = glm::radians(angles.y);
	angles.z = glm::radians(angles.z);

	if (reset)
		rotation = glm::eulerAngleYXZ(angles.y, angles.x, angles.z);
	else
		rotation *= glm::eulerAngleYXZ(angles.y, angles.x, angles.z);
}

void 				model::instance::randomize_scaling(const float_range &range)
{
	scale(random(range));
}

void 				model::instance::randomize_translation(const vec3_range &range)
{
	translate(random(range));
}

void 				model::instance::randomize_rotation(const vec3_range &range)
{
	rotate(random(range));
}