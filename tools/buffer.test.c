#include "buffer.h"
#include "../cc65-test.h"
#include <string.h>

void bufferTest()
{
	beginTest("Create buffer.");
	{
		char string[] = "hello";
		Buffer buffer = bufferCreate((uint8_t *)string, sizeof(string));

		assertIntDecimal("Length", buffer.length, 6);
		assertTrue("Content", buffer.content == (uint8_t *)string);
	}
	endTest();
}
