#pragma once

#include "engine/namespace.h"

#include "engine/model/instance.h"

class 					engine::model::group
{
	friend class 		engine::model::manager;
	friend class 		engine::renderer;

private :

	explicit			group(const initializer_list<instance::ptr> &list) : data(list)
						{}

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

		for (auto &item : data)
			result->data.push_back(item->copy());

		result->scaling = scaling;
		result->translation = translation;
		result->rotation = rotation;

		return (result);
	}

	void 				scale(float value);
	void 				translate(vec3 value);
	void 				rotate(vec3 angles);

private :

	list<instance::ptr>	data;

	mat4				scaling = mat4(1.0f);
	mat4				translation = mat4(1.0f);
	mat4				rotation = mat4(1.0f);
};