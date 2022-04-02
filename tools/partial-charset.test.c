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

	beginTest("PartialCharset findIndexOrAdd full.");
	{
		CharsetChar a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		CharsetChar b = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

		PartialCharset partialCharset;
		partialCharset.numUsedChars = 0;

		for (int index = 0; index < 256; ++index)
		{
			// Make the char unique.
			a[0] = (uint8_t)index;

			partialCharsetFindIndexOrAdd(&partialCharset, a);
		}

		assertIntDecimal("Charset should be full.", partialCharset.numUsedChars, 256);
		assertIntDecimal("Adding more should fail.", partialCharsetFindIndexOrAdd(&partialCharset, b), -1);
	}
	endTest();

	beginTest("PartialCharset compress.");
	{
		CharsetChar a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		CharsetChar b = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		CharsetChar c = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

		// Clear the charset.
		Charset uncompressedCharset;
		for (int index = 0; index < 256; ++index)
		{
			charsetCharCopy(a, uncompressedCharset[index]);
		}

		// Add some chars.
		charsetCharCopy(b, uncompressedCharset[1]);
		charsetCharCopy(c, uncompressedCharset[2]);
		charsetCharCopy(b, uncompressedCharset[3]);
		charsetCharCopy(c, uncompressedCharset[4]);

		PartialCharset compressedCharset;
		compressedCharset.numUsedChars = 0;
		uint8_t mappingTable[256];
		partialCharsetCompress(&compressedCharset, uncompressedCharset, mappingTable);

		assertIntDecimal("Charset should contain 3 chars.", compressedCharset.numUsedChars, 3);
		assertTrue("Charset should contain a.", charsetCharEquals(compressedCharset.charset[0], a));
		assertTrue("Charset should contain b.", charsetCharEquals(compressedCharset.charset[1], b));
		assertTrue("Charset should contain c.", charsetCharEquals(compressedCharset.charset[2], c));
		assertIntDecimal("Mapping should contain a.", mappingTable[0], 0);
		assertIntDecimal("Mapping should contain b.", mappingTable[1], 1);
		assertIntDecimal("Mapping should contain c.", mappingTable[2], 2);
		assertIntDecimal("Mapping should contain b.", mappingTable[3], 1);
		assertIntDecimal("Mapping should contain c.", mappingTable[4], 2);
		assertIntDecimal("Mapping should contain a.", mappingTable[5], 0);
	}
	endTest();
}
