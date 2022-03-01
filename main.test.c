#include "cc65-test.h"
#include "circular-buffer.test.h"
#include "coord.test.h"
#include "tile.test.h"
#include "worm.test.h"

int main(void)
{

	beforeTests();

	coordTest();
	circularBufferTest();
	tileTest();
	wormTest();

	afterTests();

	return 0;
}
