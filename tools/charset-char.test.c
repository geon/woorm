#include "charset-char.h"
#include "../cc65-test.h"
#include <stdbool.h>
#include <stdint.h>

void charsetCharTest()
{
	beginTest("CharsetChar equals.");
	{
		CharsetChar a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		CharsetChar b = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

		assertTrue("a == a", charsetCharEquals(a, a));
		assertTrue("a != b", !charsetCharEquals(a, b));
	}
	endTest();
}
