#include "../cc65-test.h"
#include "buffer.test.h"
#include "charset-char.test.h"
#include "charset.test.h"
#include "partial-charset.test.h"
#include "tile.legacy.test.h"

int main(void)
{

	beforeTests();

	tileLegacyTest();
	charsetCharTest();
	charsetTest();
	partialCharsetTest();
	bufferTest();

	afterTests();

	return 0;
}
