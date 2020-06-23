#include "room.h"

using namespace		game;

void				room::row::move(const vec3 &value)
{
	group->translate(value);

	if (obstacle)
	{
		obstacle->instance->edit_translation(2, group->translation().z);
		obstacle->does_trigger_collision = true;
		obstacle->enable(true);
	}
}



void				room::row::make_hollow(bool state)
{
	make_hollow_internal(state);
	is_hollow = state;
}

void 				room::row::make_hollow_temporarily(bool state)
{
	make_hollow_internal(is_hollow or state);
}

void				room::row::make_hollow_internal(bool state)
{
	group->hollow(state);
	if (obstacle)
		obstacle->instance->hollow(state);
}

void				room::row::link_obstacle(const obstacle::obstacle::ptr &obstacle)
{
	this->obstacle = obstacle;
}

void				room::row::unlink_obstacle()
{
	if (obstacle)
	{
		scene::scene::forget(this->obstacle);
		this->obstacle = nullptr;
	}
}

bool				room::row::does_intersects(const float_range &character_range) const
{
	float_range		my_range = room::row_range + group->translation().z;

	return (my_range or character_range);
}

model::group::ptr	room::row::read_group() const
{
	return (group);
}

line_wrapper		room::row::blocked_lines() const
{
	static auto 	lines_blocked_when_hollow = line_wrapper(line::left) | line_wrapper(line::middle) | line_wrapper(line::right);

	if (is_hollow)
		return (lines_blocked_when_hollow);
	else if (obstacle)
		return (obstacle->blocked_lines);
	else
		return {};
}

state_wrapper		room::row::blocked_states() const
{
	static auto 	states_blocked_when_hollow = state_wrapper(state::running);

	if (is_hollow)
		return (states_blocked_when_hollow);
	else if (obstacle)
		return (obstacle->blocked_states);
	else
		return {};
}