#include "engine/namespace.h"

using namespace				engine;

struct settings				&engine::settings()
{
	static struct settings	value;

	return (value);
}