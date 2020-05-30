#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"

class						engine::model::instance
{
	friend class			engine::model::manager;
	friend class			engine::renderer;

private :

	explicit 				instance(model::ptr model) :
							model(model)
							{}
public :
							~instance() = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(instance)

	ptr						copy() const
	{
		auto				result = make_ptr(model);

		result->scaling = scaling;
		result->translation = translation;
		result->rotation = rotation;

		return (result);
	}

	void 					scale(float value, bool reset = false);
	void 					translate(vec3 value, bool reset = false);
	void 					rotate(vec3 angles, bool reset = false);

	void 					randomize_scaling(const float_range &range);
	void 					randomize_translation(const vec3_range &range);
	void 					randomize_rotation(const vec3_range &range);

private :

	model::ptr 				model;

	mat4					scaling = mat4(1.0f);
	mat4					translation = mat4(1.0f);
	mat4					rotation = mat4(1.0f);
};