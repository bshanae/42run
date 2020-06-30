#include "UI/namespace.h"

using namespace 			UI;

struct sources				&UI::sources()
{
	static struct sources	value;

	return (value);
}
