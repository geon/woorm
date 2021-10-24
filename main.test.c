#include "cc65-test.h"
#include "circular-buffer.test.h"

int main()
{

	beforeTests();

	circularBufferTest();

	afterTests();

	return 0;
}
