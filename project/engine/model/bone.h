#pragma once

#include "engine/namespace.h"

#include "engine/converter/converter.h"

class					engine::model::bone
{
public :

	string				name;
	int 				id;

	aiNode				*node = nullptr;
	aiNodeAnim			*animation = nullptr;

	bone				*parent = nullptr;
	mat4 				offset;

	vec3 				position = vec3(0.f);
	quat				rotation = quat(0.f, 0.f, 0.f, 0.f);
	vec3 				scale = vec3(0.f);

						bone(int id, const string &name, const mat4 &offset) :
						id(id),
						name(name),
						offset(offset)
						{}
						~bone() = default;

	void				update_keyframe_transformation(float time);

private :

	[[nodiscard]] mat4	get_parents_transformation() const;

	[[nodiscard]] vec3	interpolate_position(float time) const;
	[[nodiscard]] quat	interpolate_rotation(float time) const;

	[[nodiscard]] int	find_position(float time) const;
	[[nodiscard]] int	find_rotation(float time) const;
};