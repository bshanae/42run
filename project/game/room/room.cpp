#include "room.h"

using namespace					game;

								room::room()
{
	vec3 						shift;
	model::manager::flags_wrap	flags;

	//							Model

	flags = model::manager::flags::center;
	model = model::manager::make_model(path, flags);

	//							Instances

	model::instance::ptr		instances[2];

	instances[0] = engine::model::manager::make_instance(model);
	instances[1] = engine::model::manager::make_instance(model);

	shift = vec3();
	shift.x = model->read_size().x / 2.f;

	instances[0]->translate(shift * vec3(-1.f));
	instances[1]->translate(shift * vec3(+1.f));
	instances[1]->rotate(vec3(0, 180, 0));

	//							Groups

	for (auto &group : groups)
		group = engine::model::group::make_ptr({instances[0], instances[1]});

	shift = vec3();
	shift.z = -1.f * model->read_size().z;

	for (int i = 1; i < 10; i++)
		groups[i]->translate(shift * vec3(static_cast<float>(i)));

	for (auto &group : groups)
		engine::renderer::target(group);
}