#pragma once

#include "engine/namespace.h"

#include "engine/abstract/pointer.h"
#include "engine/model/material.h"
#include "engine/model/mesh.h"
#include "engine/model/skeleton.h"
#include "engine/model/animation.h"

class							engine::model::model
{
public :

	friend class				manager;
	friend class 				engine::renderer;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(model)

private :
								model(
								vector<mesh::ptr> &meshes,
								skeleton::ptr &skeleton) :
								meshes(move(meshes)),
								skeleton(move(skeleton))
								{}

public:
								~model() = default;

	void						animate(const animation &animation)
	{
		skeleton->animate(animation);
	}

	void						analyze();
	void						center();

	[[nodiscard]] vec3			read_min() const
	{
		if (not is_analyzed)
			common::warning::raise(common::warning::id::model_is_not_analyzed);
		return (min);
	}

	[[nodiscard]] vec3			read_max() const
	{
		if (not is_analyzed)
			common::warning::raise(common::warning::id::model_is_not_analyzed);
		return (max);
	}

	[[nodiscard]] vec3			read_size() const
	{
		if (not is_analyzed)
			common::warning::raise(common::warning::id::model_is_not_analyzed);
		return (size);
	}

private:

	vector<mesh::ptr>			meshes;
	skeleton::ptr				skeleton;

	bool						is_analyzed = false;
	vec3						min;
	vec3						max;
	vec3						size;
};

