#include "scene.h"

using namespace		engine;

void				scene::scene::target(const model::model::ptr &target)
{
	instance()->targets.models.push_back(target);
}

void				scene::scene::target(const model::instance::ptr &target)
{
	instance()->targets.instances.push_back(target);
}

void				scene::scene::target(const model::group::ptr &target)
{
	instance()->targets.groups.push_back(target);
}

void				scene::scene::connect_to_global()
{
	global().scene = instance();
}