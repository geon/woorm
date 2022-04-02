#include "partial-charset.h"
#include "../cc65-test.h"

void partialCharsetTest()
{
	beginTest("PartialCharset findIndexOrAdd.");
	{
		CharsetChar a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		CharsetChar b = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

		PartialCharset partialCharset;
		partialCharset.numUsedChars = 0;

		assertIntDecimal("Char should be added at the first available index.", partialCharsetFindIndexOrAdd(&partialCharset, a), 0);
		assertTrue("Char a should be added.", charsetCharEquals(partialCharset.charset[0], a));
		assertIntDecimal("Char usage should increase.", partialCharset.numUsedChars, 1);

		assertIntDecimal("Next char should be added at the new first available index.", partialCharsetFindIndexOrAdd(&partialCharset, b), 1);
		assertIntDecimal("Char usage should increase.", partialCharset.numUsedChars, 2);

		assertIntDecimal("Char a should be found.", partialCharsetFindIndexOrAdd(&partialCharset, a), 0);
		assertIntDecimal("Char usage should stay the same.", partialCharset.numUsedChars, 2);
	}
	endTest();
}
