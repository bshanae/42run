#include "bone.h"

using namespace		engine;

void				model::bone::update_keyframe_transformation(float time)
{
	if (not animation)
		return ;

	scale = vec3(1.f);
	position = interpolate_position(time);
	rotation = interpolate_rotation(time);

	auto			result = mat4(1.0f);

	result *= glm::scale(scale);
	result *= glm::translate(position);
	result *= glm::mat4_cast(rotation);

	node->mTransformation = converter::to_assimp(result);
}

mat4				model::bone::get_parents_transformation() const
{
	bone::ptr		iterator = parent;
	vector<mat4>	matrices;
	mat4			result(1.0f);

	while (iterator)
	{
		matrices.push_back(converter::to_glm(iterator->node->mTransformation));
		iterator = iterator->parent;
	}

	for (int i = matrices.size() - 1; i >= 0; i--)
		result *= matrices[i];

	return (result);
}

vec3				model::bone::interpolate_position(float time) const
{
	if (animation->mNumPositionKeys == 1)
		return (converter::to_glm(animation->mPositionKeys[0].mValue));

	const int		begin_index = find_position(time);
	const int		end_index = begin_index + 1;

	const auto		time_delta = (float)(animation->mPositionKeys[end_index].mTime - animation->mPositionKeys[begin_index].mTime);
	const auto		factor = (time - (float)animation->mPositionKeys[begin_index].mTime) / time_delta;

	const auto		begin_position = converter::to_glm(animation->mPositionKeys[begin_index].mValue);
	const auto		end_position = converter::to_glm(animation->mPositionKeys[end_index].mValue);

	return (glm::mix(begin_position, end_position, factor));
}

quat				model::bone::interpolate_rotation(float time) const
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

int					model::bone::find_position(float time) const
{
	for (int i = 0; i < animation->mNumPositionKeys - 1; i++)
		if (time < animation->mPositionKeys[i + 1].mTime)
			return (i);

	return (-1);
}

int					model::bone::find_rotation(float time) const
{
	for (int i = 0; i < animation->mNumRotationKeys - 1; i++)
		if (time < animation->mRotationKeys[i + 1].mTime)
			return (i);

	return (-1);
}