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

	void 					scale(float value);
	void 					translate(vec3 value);
	void 					rotate(vec3 angles);

private :

	model::ptr 				model;

	mat4					scaling = mat4(1.0f);
	mat4					translation = mat4(1.0f);
	mat4					rotation = mat4(1.0f);
};