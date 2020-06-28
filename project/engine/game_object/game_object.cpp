#include "game_object.h"

using namespace		engine;

void				game_object::game_object::start()
{
	if (state != state::waiting)
		error::raise(error::id::game_object_bad_logic);

	state = state::working;
	list.push_back(shared_from_this());
}

void				game_object::game_object::pause(bool state)
{
	if (this->state != state::working and this->state != state::paused)
		error::raise(error::id::game_object_bad_logic);

	this->state = state ? state::paused : state::working;
}

void				game_object::game_object::stop()
{
	auto			iterator = find(list.begin(), list.end(), shared_from_this());

	state = state::stopped;
	if (iterator == list.end())
		list.erase(iterator);
}

void				game_object::game_object::render_target(const shared<model::instance> &target)
{
	render_targets.instances.push_back(target);
}

void				game_object::game_object::render_target(const shared<model::group> &target)
{
	render_targets.groups.push_back(target);
}

void				game_object::game_object::animation_target(const shared<model::model> &target)
{
	animation_targets.push_back(target);
}