#include "cc65-test.h"
#include "circular-buffer.test.h"
#include "coord.test.h"
#include "lz77-back-reference.test.h"
#include "lz77.test.h"
#include "worm.test.h"

int main(void)
{

	beforeTests();

	coordTest();
	circularBufferTest();
	wormTest();
	lz77BackReferenceTest();
	lz77Test();

	afterTests();

	return 0;
}
