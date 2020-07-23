#include "room.h"

#include "game/engine_extensions/instance.h"
#include "game/engine_extensions/group.h"

using namespace						game;

void								room::row::move(const vec3 &value)
{
	group->translate(value);

	if (obstacle)
	{
		obstacle->instance->edit_translation(2, group->translation().z);
		obstacle->pause(false);
	}
	if (bonus)
	{
		bonus->instance->edit_translation(2, group->translation().z);
		bonus->pause(false);
	}
}

void								room::row::make_hollow(bool state)
{
	make_hollow_internal(state);
	is_hollow = state;
}

void 								room::row::make_hollow_temporarily(bool state)
{
	make_hollow_internal(is_hollow or state);
}

void								room::row::make_hollow_internal(bool state)
{
	group->hollow(state);
	if (obstacle)
		obstacle->instance->hollow(state);
}

void								room::row::link_obstacle(const shared<obstacle::obstacle> &obstacle)
{
	if (obstacle)
	{
		this->obstacle = obstacle;
		this->obstacle->start();
		obstacle->pause(true);
	}
	else if (this->obstacle)
	{
		this->obstacle->stop();
		this->obstacle = nullptr;
	}
}

void								room::row::link_bonus(const shared<bonus::bonus> &bonus)
{
	if (bonus)
	{
		this->bonus = bonus;
		this->bonus->start();
		bonus->pause(true);
	}
	else if (this->bonus)
	{
		this->bonus->stop();
		this->bonus = nullptr;
	}
}

shared<engine_extensions::group>	room::row::read_group() const
{
	return (group);
}

bool								room::row::does_collide(const float_range &character_range) const
{
	float_range						my_range = room::row_range + group->translation().z;

	return (my_range or character_range);
}

bool								room::row::does_collide_with_obstacle(line character_line, const state_wrapper &character_state) const
{
	if
	(
		is_hollow and
		lines_blocked_by_hollow_row.does_intersect(character_line) and
		states_blocked_by_hollow_row.does_intersect(character_state)
	)
		return (true);
	if
	(
		obstacle and
		obstacle->blocked_lines.does_intersect(character_line) and
		obstacle->blocked_states.does_intersect(character_state)
	)
		return (true);
	return (false);
}

pair<bool, shared<bonus::bonus>>	room::row::does_collide_with_bonus(line character_line, const state_wrapper &character_state) const
{
	if
	(
		bonus and
		bonus->used_lines.does_intersect(character_line) and
		bonus->used_states.does_intersect(character_state)
	)
		return {true, bonus};
	return {false, nullptr};
}

bool								room::row::is_line_free(line_wrapper line)
{
	if (is_hollow)
		return (false);
	if (obstacle and (obstacle->blocked_lines.does_intersect(line)))
		return (false);
	if (bonus and (bonus->used_lines.does_intersect(line)))
		return (false);
	return (true);
}