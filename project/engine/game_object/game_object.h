#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class 					engine::game_object
{
	friend class		engine::scene::scene;
	friend class		engine::renderer;

public :

						game_object() = default;
	virtual				~game_object() = default;

IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(game_object)

protected :

	virtual void		update()
	{}

	void				target(const model::instance::ptr &target)
	{
		targets.instances.push_back(target);
	}

	void				target(const model::group::ptr &target)
	{
		targets.groups.push_back(target);
	}

private :

	struct
	{
		using			instances_type = vector<model::instance::ptr>;
		using			groups_type = vector<model::group::ptr>;

		instances_type	instances;
		groups_type		groups;
	}					targets;
};