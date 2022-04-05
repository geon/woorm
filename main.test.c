#include "cc65-test.h"
#include "circular-buffer.test.h"
#include "coord.test.h"
#include "worm.test.h"

int main(void)
{

	beforeTests();

	coordTest();
	circularBufferTest();
	wormTest();

	afterTests();

	return 0;
}
