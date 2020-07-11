#include "room.h"

#include "game/model_with_mods/instance.h"
#include "game/model_with_mods/group.h"

using namespace					game;

void							room::row::move(const vec3 &value)
{
	group->translate(value);

	if (obstacle)
	{
		obstacle->instance->edit_translation(2, group->translation().z);
		obstacle->does_trigger_collision = true;
		obstacle->pause(false);
	}
}

void							room::row::make_hollow(bool state)
{
	make_hollow_internal(state);
	is_hollow = state;
}

void 							room::row::make_hollow_temporarily(bool state)
{
	make_hollow_internal(is_hollow or state);
}

void							room::row::make_hollow_internal(bool state)
{
	group->hollow(state);
	if (obstacle)
		obstacle->instance->hollow(state);
}

void							room::row::link_obstacle(const shared<obstacle::obstacle> &obstacle)
{
	this->obstacle = obstacle;
	this->obstacle->start();
	obstacle->pause(true);
}

void							room::row::unlink_obstacle()
{
	if (obstacle)
	{
		obstacle->stop();
		obstacle = nullptr;
	}
}

bool							room::row::does_intersect(const float_range &character_range) const
{
	float_range					my_range = room::row_range + group->translation().z;

	return (my_range or character_range);
}

shared<model_with_mods::group>	room::row::read_group() const
{
	return (group);
}

line_wrapper					room::row::blocked_lines() const
{
	static auto 				lines_blocked_when_hollow = line_wrapper(line::left) | line_wrapper(line::middle) | line_wrapper(line::right);

	if (is_hollow)
		return (lines_blocked_when_hollow);
	else if (obstacle)
		return (obstacle->blocked_lines);
	else
		return {};
}

state_wrapper			room::row::blocked_states() const
{
	static auto 		states_blocked_when_hollow = state_wrapper(state::running);

	if (is_hollow)
		return (states_blocked_when_hollow);
	else if (obstacle)
		return (obstacle->blocked_states);
	else
		return {};
}