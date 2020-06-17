#include "group.h"

using namespace		engine;

					model::group::group(const initializer_list<instance::ptr> &list) :
					instances(list)
{
	reset_scaling();
	reset_translation();
	reset_rotation();
}

void				model::group::scale(float value)
{
	data.scaling *= vec3(value);
	transformations.scaling = glm::scale(data.scaling);
}

void				model::group::translate(vec3 value)
{
	data.translation += value;
	transformations.translation = glm::translate(data.translation);
}

void				model::group::rotate(vec3 angles)
{
	angles.x = radians(angles.x);
	angles.y = radians(angles.y);
	angles.z = radians(angles.z);

	data.rotation += angles;
	transformations.rotation = glm::eulerAngleYXZ(data.rotation.y, data.rotation.x, data.rotation.z);
}

void 				model::group::reset_scaling()
{
	data.scaling = vec3(1.f);
	transformations.scaling = mat4(1.0f);
}

void 				model::group::reset_translation()
{
	data.translation = vec3(0.f);
	transformations.translation = mat4(1.0f);
}

void 				model::group::reset_rotation()
{
	data.rotation = vec3(0.f);
	transformations.rotation = mat4(1.0f);
}
