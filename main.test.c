#include "cc65-test.h"
#include "circular-buffer.test.h"
#include "coord.test.h"
#include "tile.test.h"

int main()
{

	beforeTests();

	coordTest();
	circularBufferTest();
	tileTest();

	afterTests();

	return 0;
}
