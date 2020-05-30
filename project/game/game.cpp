#include "game/namespace.h"

using namespace 			game;

struct sources				&game::sources()
{
	static struct sources	value;

	return (value);
}