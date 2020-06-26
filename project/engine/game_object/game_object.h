#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class 						engine::game_object::game_object
{
	friend class			engine::core;
	friend class			engine::scene::scene;
	friend class			engine::game_object::reader;

public :

	explicit				game_object(const shared<renderer> &renderer = nullptr) :
								renderer(renderer)
							{}
	virtual					~game_object() = default;

protected :

	virtual void			update()
	{}

	void					render_target(const shared<model::instance> &target)
	{
		render_targets.instances.push_back(target);
	}

	void					render_target(const shared<model::group> &target)
	{
		render_targets.groups.push_back(target);
	}

	void					animation_target(const shared<model::model> &target)
	{
		animation_targets.push_back(target);
	}

public :

	using					models_type = vector<shared<model::model>>;
	using					instances_type = vector<shared<model::instance>>;
	using					groups_type = vector<shared<model::group>>;

	struct					render_targets
	{
		instances_type		instances;
		groups_type			groups;
	};

	bool					is_enabled = true;

private :

	const shared<renderer>	renderer;

	render_targets			render_targets;
	models_type				animation_targets;
};