#include "coord.h"
#include "cc65-test.h"
#include "custom-asserts.h"
#include <stdio.h>

void coordTest(void)
{
	beginTest("Create coord.");
	{
		assertByteDecimal("coord.x", coordCreate(10, 20).x, 10);
		assertByteDecimal("coord.y", coordCreate(10, 20).y, 20);
	}
	endTest();

	beginTest("Convert coord and position.");
	{
		assertCoord("posToCoord 1", posToCoord(coordToPos(coordCreate(10, 10))), coordCreate(10, 10));
		assertCoord("posToCoord 2", posToCoord(coordToPos(coordCreate(34, 12))), coordCreate(34, 12));
		assertWordDecimal("coordToPos 1", coordToPos(posToCoord(0)), 0);
		assertWordDecimal("coordToPos 2", coordToPos(posToCoord(999)), 999);
		assertWordDecimal("coordToPos 3", coordToPos(posToCoord(410)), 410);
		assertWordDecimal("coordToPos 4", coordToPos(posToCoord(321)), 321);
	}
	endTest();
}
