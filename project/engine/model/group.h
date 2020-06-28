#pragma once

#include "engine/namespace.h"

#include "engine/model/instance.h"

class 						engine::model::group
{
	friend class 			engine::model::manager;
	friend class 			engine::model::reader;

public :
							group();
							~group() = default;

	void					include(const shared<engine::model::instance> &instance);

	shared<group>			copy() const;

	vec3					scaling() const
	{
		return (data.scaling);
	}

	vec3					translation() const
	{
		return (data.translation);
	}

	vec3					rotation() const
	{
		return (data.rotation);
	}

	void 					scale(float value);
	void 					translate(vec3 value);
	void 					rotate(vec3 angles);

	void 					reset_scaling();
	void 					reset_translation();
	void 					reset_rotation();

	void					hollow(bool state)
	{
		for (auto &instance : instances)
			instance->hollow(state);
	}

private :

	list<shared<instance>>	instances;

	struct
	{
		vec3				scaling;
		vec3				translation;
		vec3				rotation;
	}						data;

	struct
	{
		mat4				scaling;
		mat4				translation;
		mat4				rotation;
	}						transformations;
};