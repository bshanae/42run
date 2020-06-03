#include "room.h"

using namespace					game;

								room::room()
{

	build_models();
	build_main_instances();
	build_unique_groups();
	offset_groups();
	target();
}

void							room::build_models()
{
	model::flags_wrap			analyze_flag = model::flags::analyze;
	model::flags_wrap			center_flag = model::flags::center;

	models.room = model::manager::make_model(sources().room, analyze_flag);
	models.chair = model::manager::make_model(sources().chair, center_flag);
	models.mac = model::manager::make_model(sources().mac, center_flag);
	models.keyboard = model::manager::make_model(sources().keyboard, center_flag);
}

void							room::build_main_instances()
{
	auto						&main_instances = instances[0];

//								Construction

	main_instances.room = engine::model::manager::make_instance(models.room);
	for (int i = 0; i < number_of_accessories; i++)
	{
		main_instances.chair[i] = engine::model::manager::make_instance(models.chair);
		main_instances.mac[i] = engine::model::manager::make_instance(models.mac);
		main_instances.keyboard[i] = engine::model::manager::make_instance(models.keyboard);
	}

//								Transformation

	for (int i = 0; i < number_of_accessories; i++)
	{
//								Interval between each mac
		main_instances.chair[i]->translate(models.chair->read_offset() + intervals.little * vec3(i));
		main_instances.mac[i]->translate(models.mac->read_offset() + intervals.little * vec3(i));
		main_instances.keyboard[i]->translate(models.keyboard->read_offset() + intervals.little * vec3(i));

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

void							room::build_unique_groups()
{
//								Copy instances
	for (int group_i = 1; group_i < number_of_groups; group_i++)
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
	for (int group_i = 0; group_i < number_of_groups; group_i++)
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
	for (int group_i = 0; group_i < number_of_groups; group_i++)
		groups[group_i] = model::manager::make_group(
		{
			instances[group_i].room,
			instances[group_i].chair[0],
			instances[group_i].chair[1],
			instances[group_i].chair[2],
			instances[group_i].chair[3],
			instances[group_i].chair[4],
			instances[group_i].chair[5],
			instances[group_i].chair[6],
			instances[group_i].chair[7],
			instances[group_i].mac[0],
			instances[group_i].mac[1],
			instances[group_i].mac[2],
			instances[group_i].mac[3],
			instances[group_i].mac[4],
			instances[group_i].mac[5],
			instances[group_i].mac[6],
			instances[group_i].mac[7],
			instances[group_i].keyboard[0],
			instances[group_i].keyboard[1],
			instances[group_i].keyboard[2],
			instances[group_i].keyboard[3],
			instances[group_i].keyboard[4],
			instances[group_i].keyboard[5],
			instances[group_i].keyboard[6],
			instances[group_i].keyboard[7]
		});
}

void							room::offset_groups()
{
	const auto					offset = (vec3){0, 0, -1.f * models.room->read_size().z};

	for (int i = 1; i < number_of_groups; i++)
		groups[i]->translate(offset * vec3(i));
}

void							room::target()
{
	for (int i = 0; i < number_of_groups; i++)
		engine::scene::scene::target(groups[i]);
}
