#include "instance.h"

using namespace		engine;

					model::instance::instance(const shared<engine::model::model> &model) :
						model(model)
{
	reset_scaling();
	reset_translation();
	reset_rotation();
}

void				model::instance::scale(float value)
{
	data.scaling *= vec3(value);
	transformations.scaling = glm::scale(data.scaling);
}

void				model::instance::translate(vec3 value)
{
	data.translation += value;
	transformations.translation = glm::translate(data.translation);
}

void				model::instance::rotate(vec3 angles)
{
	angles.x = radians(angles.x);
	angles.y = radians(angles.y);
	angles.z = radians(angles.z);

	data.rotation += angles;
	transformations.rotation = glm::eulerAngleYXZ(data.rotation.y, data.rotation.x, data.rotation.z);
}

void				model::instance::edit_translation(int component_index, float value)
{
	data.translation[component_index] = value;
	transformations.translation = glm::translate(data.translation);
}

void 				model::instance::reset_scaling()
{
	data.scaling = vec3(1.f);
	transformations.scaling = mat4(1.0f);
}

void 				model::instance::reset_translation()
{
	data.translation = vec3(0.f);
	transformations.translation = mat4(1.0f);
}

void 				model::instance::reset_rotation()
{
	data.rotation = vec3(0.f);
	transformations.rotation = mat4(1.0f);
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