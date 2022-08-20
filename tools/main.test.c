#include "../cc65-test.h"
#include "buffer.test.h"
#include "charset-char.test.h"
#include "charset.test.h"
#include "level.test.h"
#include "lz77-back-reference.test.h"
#include "lz77.test.h"
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
	lz77backReferenceTest();
	lz77Test();
	levelTest();

	afterTests();

	return 0;
}
