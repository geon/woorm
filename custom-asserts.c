#include "cc65-test.h"
#include "coord.h"
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
