#include "worm.h"
#include "cc65-test.h"

Worm _worm;
Worm *worm = &_worm;

void wormTest()
{
	beginTest("Create worm.");
	{
		wormInit(worm);
	}
	endTest();
}
