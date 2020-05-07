#pragma once

#include "engine/namespace.h"

#include "engine/model/material.h"
#include "engine/model/mesh.h"
#include "engine/model/skeleton.h"

class							engine::model::model
{
	friend class				loader;
	friend class 				engine::renderer;

private :
								model(
								vector<unique_ptr<mesh>> &meshes,
								unique_ptr<skeleton> &skeleton) :
								meshes(move(meshes)),
								skeleton(move(skeleton))
								{}
public:
								~model() = default;
private:

	vector<unique_ptr<mesh>>	meshes;
	unique_ptr<skeleton>		skeleton;
};

