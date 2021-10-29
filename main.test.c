#include "cc65-test.h"
#include "coord.test.h"
#include "circular-buffer.test.h"

int main()
{

	beforeTests();

	coordTest();
	circularBufferTest();

	afterTests();

	return 0;
}
