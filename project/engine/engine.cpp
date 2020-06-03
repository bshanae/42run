#include "engine/namespace.h"

using namespace				engine;

struct settings				&engine::settings()
{
	static struct settings	value;

	return (value);
}

void						engine::global::revise()
{
	if (not core or not renderer or not scene)
		error::raise(error::id::engine_bad_global_value);
}

struct global				&engine::global()
{
	static struct global	value;

	return (value);
}