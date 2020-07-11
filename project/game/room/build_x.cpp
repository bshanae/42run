#include "room.h"

#include "game/model_with_mods/group.h"

using namespace					game;

void							room::build_models()
{
	model::flag_wrapper			analyze_flag = model::flag::analyze;
	model::flag_wrapper			center_flag = model::flag::center;

	models.room = make_shared<model::model>(sources().room, analyze_flag);
	models.chair = make_shared<model::model>(sources().chair, center_flag);
	models.mac = make_shared<model::model>(sources().mac, center_flag);
	models.keyboard = make_shared<model::model>(sources().keyboard, center_flag);
}

void							room::build_instances()
{
	auto						&main_instances = instances[0];

//								Construction

	main_instances.room = make_shared<model_with_mods::instance>(models.room);
	for (int i = 0; i < number_of_accessories; i++)
	{
		main_instances.chair[i] = make_shared<model_with_mods::instance>(models.chair);
		main_instances.mac[i] = make_shared<model_with_mods::instance>(models.mac);
		main_instances.keyboard[i] = make_shared<model_with_mods::instance>(models.keyboard);
	}

//								Transformation

	for (int i = 0; i < number_of_accessories; i++)
	{
//								Interval between each mac
		main_instances.chair[i]->translate(models.chair->offset() + intervals.little * vec3(i));
		main_instances.mac[i]->translate(models.mac->offset() + intervals.little * vec3(i));
		main_instances.keyboard[i]->translate(models.keyboard->offset() + intervals.little * vec3(i));

		if (i % 2)
		{
//								Rotate accessories
			main_instances.chair[i]->rotate(vec3(0, 180, 0));
			main_instances.mac[i]->rotate(vec3(0, 180, 0));
			main_instances.keyboard[i]->rotate(vec3(0, 180, 0));

//								Move rotated accessories
			main_instances.chair[i]->translate(jumps.chair);
			main_instances.mac[i]->translate(jumps.mac);
			main_instances.keyboard[i]->translate(jumps.keyboard);
		}

//								Move to right table
		if (i >= 4)
		{
			main_instances.chair[i]->translate(intervals.big);
			main_instances.mac[i]->translate(intervals.big);
			main_instances.keyboard[i]->translate(intervals.big);
		}
	}
}

void							room::build_groups()
{
//								Copy instances
	for (int group_i = 1; group_i < number_of_rows; group_i++)
	{
		instances[group_i].room = instances[0].room->copy();
		for (int accessory_i = 0; accessory_i < number_of_accessories; accessory_i++)
		{
			instances[group_i].chair[accessory_i] = instances[0].chair[accessory_i]->copy();
			instances[group_i].mac[accessory_i] = instances[0].mac[accessory_i]->copy();
			instances[group_i].keyboard[accessory_i] = instances[0].keyboard[accessory_i]->copy();
		}
	}

//								Randomize
	for (int group_i = 0; group_i < number_of_rows; group_i++)
		for (int accessory_i = 0; accessory_i < number_of_accessories; accessory_i++)
			if (accessory_i % 2 == 0)
			{
				instances[group_i].chair[accessory_i]->randomize_translation(translation_ranges.chair);
				instances[group_i].keyboard[accessory_i]->randomize_translation(translation_ranges.keyboard);

				instances[group_i].chair[accessory_i]->randomize_rotation(rotation_ranges.chair);
				instances[group_i].keyboard[accessory_i]->randomize_rotation(rotation_ranges.keyboard);
			}
			else
			{
				instances[group_i].chair[accessory_i]->randomize_translation(translation_ranges.chair * -1.f);
				instances[group_i].keyboard[accessory_i]->randomize_translation(translation_ranges.keyboard * -1.f);

				instances[group_i].chair[accessory_i]->randomize_rotation(rotation_ranges.chair * -1.f);
				instances[group_i].keyboard[accessory_i]->randomize_rotation(rotation_ranges.keyboard * -1.f);
			}

//								Build groups
	for (int row_i = 0; row_i < number_of_rows; row_i++)
	{
		auto					group = make_shared<model_with_mods::group>();

		group->include(instances[row_i].room);
		for (int accessory_i = 0; accessory_i < number_of_accessories; accessory_i++)
		{
			group->include(instances[row_i].chair[accessory_i]);
			group->include(instances[row_i].mac[accessory_i]);
			group->include(instances[row_i].keyboard[accessory_i]);
		}

		game_object::render_target(group);
		rows.push_back(make_shared<row>(group));
	}
}