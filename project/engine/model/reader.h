#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class					engine::model::reader
{
public :
						reader() = default;
	virtual				~reader() = default;

protected :

//						Model
	[[nodiscard]]
	inline const auto	&meshes(const shared<engine::model::model> &model) const
	{
		return (model->meshes);
	}

	[[nodiscard]]
	inline const auto	&skeleton(const shared<engine::model::model> &model) const
	{
		return (model->skeleton);
	}

	[[nodiscard]]
	inline const auto	&analysis(const shared<engine::model::model> &model) const
	{
		return (model->analysis);
	}

//						Mesh
	[[nodiscard]]
	inline const auto	&material(const unique<engine::model::mesh> &mesh) const
	{
		return (mesh->material);
	}

	[[nodiscard]]
	inline const auto	&indices(const unique<engine::model::mesh> &mesh) const
	{
		return (mesh->indices);
	}

	[[nodiscard]]
	inline const auto	&VAO(const unique<engine::model::mesh> &mesh) const
	{
		return (mesh->VAO);
	}

//						Skeleton
	[[nodiscard]]
	inline const auto	&bones(const unique<engine::model::skeleton> &skeleton) const
	{
		return (skeleton->bones);
	}

//						Texture
	[[nodiscard]]
	inline const auto	object(const unique<engine::model::texture> &texture) const
	{
		return (texture->object);
	}

//						Instance
	[[nodiscard]]
	inline const auto	&model(const shared<engine::model::instance> &instance) const
	{
		return (instance->model);
	}

	[[nodiscard]]
	inline const auto	&scaling(const shared<engine::model::instance> &instance) const
	{
		return (instance->transformations.scaling);
	}

	[[nodiscard]]
	inline const auto	&translation(const shared<engine::model::instance> &instance) const
	{
		return (instance->transformations.translation);
	}

	[[nodiscard]]
	inline const auto	&rotation(const shared<engine::model::instance> &instance) const
	{
		return (instance->transformations.rotation);
	}

	[[nodiscard]]
	inline bool			is_hollow(const shared<engine::model::instance> &instance) const
	{
		return (instance->is_hollow);
	}


	//						Group
	[[nodiscard]]
	inline const auto	&instances(const shared<engine::model::group> &group) const
	{
		return (group->instances);
	}

	[[nodiscard]]
	inline const auto	&scaling(const shared<engine::model::group> &group) const
	{
		return (group->transformations.scaling);
	}

	[[nodiscard]]
	inline const auto	&translation(const shared<engine::model::group> &group) const
	{
		return (group->transformations.translation);
	}

	[[nodiscard]]
	inline const auto	&rotation(const shared<engine::model::group> &group) const
	{
		return (group->transformations.rotation);
	}
};