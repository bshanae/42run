#pragma once

#include "engine/namespace.h"

#include "engine/model/instance.h"

class 					engine::model::group
{
	friend class 		engine::model::manager;
	friend class 		engine::renderer;

private :

	explicit			group(const initializer_list<instance::ptr> &list);

public :
						~group() = default;

	using				ptr = shared_ptr<group>;

	static inline auto	make_ptr(const initializer_list<instance::ptr> &list)
	{
		auto			*raw = new group(list);

		return (shared_ptr<group>(raw));
	}

	ptr					copy() const
	{
		auto			result = make_ptr({});

		for (auto &instance : instances)
			result->instances.push_back(instance->copy());

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

	void 					reset_scaling();
	void 					reset_translation();
	void 					reset_rotation();

private :

	list<instance::ptr>		instances;

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