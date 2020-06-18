#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class 					engine::game_object
{
	friend class		engine::core;
	friend class		engine::renderer;
	friend class		engine::scene::scene;

public :

						game_object() = default;
	virtual				~game_object() = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(game_object)

protected :

	virtual void		update()
	{}

	void				render_target(const model::instance::ptr &target)
	{
		render_targets.instances.push_back(target);
	}

	void				render_target(const model::group::ptr &target)
	{
		render_targets.groups.push_back(target);
	}

	void				animation_target(const model::model::ptr &target)
	{
		animation_targets.push_back(target);
	}

private :

	using				models_type = vector<model::model::ptr>;
	using				instances_type = vector<model::instance::ptr>;
	using				groups_type = vector<model::group::ptr>;

	struct
	{
		instances_type	instances;
		groups_type		groups;
	}					render_targets;

	models_type			animation_targets;
};