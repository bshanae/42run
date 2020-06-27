#include "game/namespace.h"

using namespace 			game;

struct sources				&game::sources()
{
	static struct sources	value;

	return (value);
}

struct settings				&game::settings()
{
	static struct settings	value;

	return (value);
}

struct global				&game::global()
{
	static struct global	value;

	return (value);
}