#include "coord.h"
#include "cc65-test.h"

void coordTest()
{
	beginTest("Create coord.");
	{
		assertByteDecimal("coord.x", coordCreate(10, 20).x, 10);
		assertByteDecimal("coord.y", coordCreate(10, 20).y, 20);
	}
	endTest();
}
