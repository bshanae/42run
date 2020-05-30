#include "room.h"

using namespace					game;

								room::room()
{
	model::flags_wrap			center_flag = model::flags::center;

//								Model

	models.room = model::manager::make_model(sources().room);
	models.chair = model::manager::make_model(sources().chair, center_flag);
	models.mac = model::manager::make_model(sources().mac, center_flag);
	models.keyboard = model::manager::make_model(sources().keyboard, center_flag);

//								Instances

	instances.room = engine::model::manager::make_instance(models.room);
	for (int i = 0; i < 8; i++)
	{
		instances.chair[i] = engine::model::manager::make_instance(models.chair);
		instances.mac[i] = engine::model::manager::make_instance(models.mac);
		instances.keyboard[i] = engine::model::manager::make_instance(models.keyboard);
	}

//								Transformations

	for (int i = 0; i < 8; i++)
	{
//								Interval between each mac
		instances.chair[i]->translate(models.chair->read_offset() + intervals.little * vec3(i));
		instances.mac[i]->translate(models.mac->read_offset() + intervals.little * vec3(i));
		instances.keyboard[i]->translate(models.keyboard->read_offset() + intervals.little * vec3(i));

		if (i % 2)
		{
//								Rotate accessories
			instances.chair[i]->rotate(vec3(0, 180, 0));
			instances.mac[i]->rotate(vec3(0, 180, 0));
			instances.keyboard[i]->rotate(vec3(0, 180, 0));

//								Move rotated accessories
			instances.chair[i]->translate(jumps.chair);
			instances.mac[i]->translate(jumps.mac);
			instances.keyboard[i]->translate(jumps.keyboard);
		}

//								Move to right table
		if (i >= 4)
		{
			instances.chair[i]->translate(intervals.big);
			instances.mac[i]->translate(intervals.big);
			instances.keyboard[i]->translate(intervals.big);
		}
	}

//								Groups

	groups[0] = model::manager::make_group(
	{
		instances.room,
		instances.chair[0],
		instances.chair[1],
		instances.chair[2],
		instances.chair[3],
		instances.chair[4],
		instances.chair[5],
		instances.chair[6],
		instances.chair[7],
		instances.mac[0],
		instances.mac[1],
		instances.mac[2],
		instances.mac[3],
		instances.mac[4],
		instances.mac[5],
		instances.mac[6],
		instances.mac[7],
		instances.keyboard[0],
		instances.keyboard[1],
		instances.keyboard[2],
		instances.keyboard[3],
		instances.keyboard[4],
		instances.keyboard[5],
		instances.keyboard[6],
		instances.keyboard[7]
	});

//								Randomization

	for (int i = 0; i < 8; i++)
		if (i % 2 == 0)
		{
			instances.chair[i]->randomize_translation(translation_ranges.chair);
			instances.keyboard[i]->randomize_translation(translation_ranges.keyboard);
		}
		else
		{
			instances.chair[i]->randomize_translation(translation_ranges.chair * -1.f);
			instances.keyboard[i]->randomize_translation(translation_ranges.keyboard * -1.f);
		}

	for (int i = 0; i < 8; i++)
		if (not (i % 2))
		{
			instances.chair[i]->randomize_rotation(rotation_ranges.chair);
			instances.keyboard[i]->randomize_rotation(rotation_ranges.keyboard);
		}
		else
		{
			instances.chair[i]->randomize_rotation(rotation_ranges.chair * -1.f);
			instances.keyboard[i]->randomize_rotation(rotation_ranges.keyboard * -1.f);
		}

//								Targets

	engine::renderer::target(instances.room);

	for (int i = 0; i < 8; i++)
	{
		engine::renderer::target(instances.chair[i]);
		engine::renderer::target(instances.mac[i]);
		engine::renderer::target(instances.keyboard[i]);
	}

//
//	//							Groups
//
//	for (auto &group : groups)
//		group = engine::model::group::make_ptr({instances[0]});
//
//	shift = vec3();
//	shift.z = -1.f * model->read_size().z;
//
//	for (int i = 1; i < 8; i++)
//		groups[i]->translate(shift * vec3(static_cast<float>(i)));
//
//	for (auto &group : groups)
//		engine::renderer::target(group);
}