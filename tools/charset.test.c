#include "charset.h"
#include "../cc65-test.h"

void charsetTest()
{
	beginTest("Charset indexOf.");
	{
		CharsetChar b = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		CharsetChar c = {0xCA, 0xFE, 0xBA, 0xBE, 0xDE, 0xAD, 0xBE, 0xEF};

		Charset charset = {
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
			// And so on. Not initializing the rest.
		};

		assertIntDecimal("Char b should be found.", charsetIndexOf(charset, b), 4);
		assertIntDecimal("Char c should not be found.", charsetIndexOf(charset, c), 1);
	}
	endTest();
}
