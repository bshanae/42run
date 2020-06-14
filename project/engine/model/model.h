#pragma once

#include "engine/namespace.h"

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

	[[nodiscard]] vec3			min() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analyzed.min);
	}

	[[nodiscard]] vec3			max() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analyzed.max);
	}

	[[nodiscard]] vec3			size() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analyzed.size);
	}

	[[nodiscard]] vec3			offset() const
	{
		if (not is_analyzed)
			warning::raise(warning::id::model_is_not_analyzed);
		return (analyzed.offset);
	}

private:

	void						analyze();
	void						center();

	vector<mesh::ptr>			meshes;
	skeleton::ptr				skeleton;

	bool						is_analyzed = false;
	bool						is_centered = false;

	struct
	{
		vec3					min;
		vec3					max;
		vec3					size;
		vec3					offset;
	}							analyzed;
};

