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

	void						center();

private:

	vector<mesh::ptr>			meshes;
	skeleton::ptr				skeleton;
};

