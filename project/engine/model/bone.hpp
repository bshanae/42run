#pragma once

#include "engine/namespace.h"

#include "engine/converter/converter.h"

class					engine::bone
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

	[[nodiscard]] mat4	get_parents_transformation() const
	{
		bone*			iterator = parent;
		vector<mat4>	matrices;
		mat4			result;

		while (iterator)
		{
			matrices.push_back(converter::to_glm(iterator->node->mTransformation));
			iterator = iterator->parent;
		}

		for (auto i = matrices.size() - 1; i >= 0; i--)
			result *= matrices[i];

		return (result);
	}

	[[nodiscard]] vec3	interpolate_position(float time) const
	{
		if (animation->mNumPositionKeys == 1)
			return (converter::to_glm(animation->mPositionKeys[0].mValue));

		const int		begin_index = find_position(time);
		const int		end_index = begin_index + 1;

		const auto		time_delta = (float)(animation->mPositionKeys[end_index].mTime - animation->mPositionKeys[begin_index].mTime);
		const auto		factor = (float)(time - (float)animation->mPositionKeys[begin_index].mTime) / time_delta;

		const auto		begin_position = converter::to_glm(animation->mPositionKeys[begin_index].mValue);
		const auto		end_position = converter::to_glm(animation->mPositionKeys[end_index].mValue);

		return (glm::mix(begin_position, end_position, factor));
	}

	[[nodiscard]] quat	interpolate_rotation(float time) const
	{
		if (animation->mNumRotationKeys == 1)
			return (converter::to_glm(animation->mRotationKeys[0].mValue));

		const int		begin_index = find_rotation(time);
		const int		end_index = begin_index + 1;

		const auto		time_delta = (float)(animation->mRotationKeys[end_index].mTime - animation->mRotationKeys[begin_index].mTime);
		const auto		factor = (float)(time - (float)animation->mRotationKeys[begin_index].mTime) / time_delta;

		const auto		begin_rotation = converter::to_glm(animation->mRotationKeys[begin_index].mValue);
		const auto		end_rotation = converter::to_glm(animation->mRotationKeys[end_index].mValue);

		return (glm::slerp(begin_rotation, end_rotation, factor));
	}

	[[nodiscard]] int	find_position(float time) const
	{
		for (int i = 0; i < animation->mNumPositionKeys - 1; i++)
			if (time < animation->mPositionKeys[i + 1].mTime)
				return (i);

		return (-1);
	}

	[[nodiscard]] int	find_rotation(float time) const
	{
		for (int i = 0; i < animation->mNumRotationKeys - 1; i++)
			if (time < animation->mRotationKeys[i + 1].mTime)
				return (i);

		return (-1);
	}

	void				update_keyframe_transformation(float time)
	{
		if (not animation)
			return ;

		scale = vec3(1.f);
		position = interpolate_position(time);
		rotation = interpolate_rotation(time);

		mat4			result;

		result *= glm::scale(scale);
		result *= glm::translate(position);
		result *= glm::mat4_cast(rotation);

		node->mTransformation = converter::to_assimp(result);
	}
};