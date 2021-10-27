#include "coord.h"
#include "cc65-test.h"
#include <stdio.h>

void assertCoord(char *messageString, Coord result, Coord okValue)
{
	if ((result.x != okValue.x) || (result.y != okValue.y))
	{
		char resultBuffer[11], okBuffer[11]; // 3*2+4 chars + null
		sprintf(resultBuffer, "<%*i, %*i>", 3, result.x, 3, result.y);
		sprintf(okBuffer, "<%*i, %*i>", 3, okValue.x, 3, okValue.y);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void coordTest()
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
