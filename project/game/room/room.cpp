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
	instances.chair = engine::model::manager::make_instance(models.chair);
	instances.mac = engine::model::manager::make_instance(models.mac);
	instances.keyboard = engine::model::manager::make_instance(models.keyboard);

//								Transformations

	instances.chair->translate(models.chair->read_offset());
	instances.mac->translate(models.mac->read_offset());
	instances.keyboard->translate(models.keyboard->read_offset());

//								Targets

	engine::renderer::target(instances.room);
	engine::renderer::target(instances.chair);
	engine::renderer::target(instances.mac);
	engine::renderer::target(instances.keyboard);

////	instances[0]->translate(shift * vec3(-1.f));
////	instances[1]->translate(shift * vec3(+1.f));
////	instances[1]->rotate(vec3(0, 180, 0));
//
//	//							Groups
//
//	for (auto &group : groups)
//		group = engine::model::group::make_ptr({instances[0]});
//
//	shift = vec3();
//	shift.z = -1.f * model->read_size().z;
//
//	for (int i = 1; i < 10; i++)
//		groups[i]->translate(shift * vec3(static_cast<float>(i)));
//
//	for (auto &group : groups)
//		engine::renderer::target(group);
}