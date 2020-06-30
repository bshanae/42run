#include "core.h"

using namespace		engine;

void				core::default_settings()
{
	show_polygon_back(default_settings_values::show_polygon_back);
	use_depth_test(default_settings_values::use_depth_test);
	fill_polygon(default_settings_values::fill_polygons);
}