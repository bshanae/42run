#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"

class						engine::model::instance
{
	friend class			engine::model::manager;
	friend class			engine::model::reader;

public :

	explicit 				instance(const shared<model> &model);
							~instance() = default;

	shared<instance>		copy() const
	{
		auto				result = make_shared<instance>(model);

		result->data = data;
		result->transformations = transformations;

		return (result);
	}

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

	void					edit_translation(int component_index, float value);

	void 					reset_scaling();
	void 					reset_translation();
	void 					reset_rotation();

	void 					randomize_scaling(const float_range &range);
	void 					randomize_translation(const vec3_range &range);
	void 					randomize_rotation(const vec3_range &range);

private :

	shared<model>			model;

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

public :

	const auto				&read_scaling_matrix() const
	{
		return (transformations.scaling);
	}

	const auto				&read_translation_matrix() const
	{
		return (transformations.translation);
	}

	const auto				&read_rotation_matrix() const
	{
		return (transformations.rotation);
	}
};