#pragma once

#include "engine/namespace.h"

#include "engine/model/model.h"
#include "engine/model/instance.h"
#include "engine/model/group.h"

class 							engine::game_object::game_object :
									public enable_shared_from_this<engine::game_object::game_object>
{
	friend class				engine::core;
	friend class				engine::scene::scene;
	friend class				engine::game_object::reader;

public :

	template					<typename final_type = null_renderer>
	explicit					game_object(tag<final_type> = tag<null_renderer>()) :
								renderer_code(typeid(final_type).hash_code())
								{}
	virtual						~game_object() = default;

	void						start();
	void						pause(bool state);
	void						stop();

	void						render();

protected :

	virtual void				update()
	{}

	void						render_target(const shared<model::instance> &target);
	void						render_target(const shared<model::group> &target);

	void						animation_target(const shared<model::model> &target);

public :

	using						models_type = vector<shared<model::model>>;
	using						instances_type = vector<shared<model::instance>>;
	using						groups_type = vector<shared<model::group>>;

	struct						render_targets
	{
		instances_type			instances;
		groups_type				groups;
	};

private :

	const size_t				renderer_code;

//								Filled by core
	shared<renderer>			renderer;
	enum renderer_state			renderer_state = renderer_state::not_set;

	render_targets				render_targets;
	models_type					animation_targets;

	enum state					state = state::waiting;

	static
	inline
	list<shared<game_object>>	started_objects;
};