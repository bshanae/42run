#include "room.h"

using namespace					game;

								room::room()
{
	model::manager::flags_wrap	flags;

	flags = model::manager::flags::center;
	model = model::manager::make_model(path, flags);

	instances[0] = engine::model::manager::make_instance(model);
	instances[1] = engine::model::manager::make_instance(model);

	auto						shift = model->read_size() / vec3(2);

	shift.y = 0;
	shift.z = 0;

	instances[0]->translate(shift * vec3(-1.f));
	instances[1]->translate(shift * vec3(+1.f));
	instances[1]->rotate(vec3(0, 180, 0));

	engine::renderer::add_target(instances[0]);
	engine::renderer::add_target(instances[1]);
}