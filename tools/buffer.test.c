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

	beginTest("Create buffer from string.");
	{
		Buffer buffer = bufferCreateFromString("hello");

		assertIntDecimal("Length", buffer.length, 5);
		assertTrue("Content", buffer.content[0] == 'h');
		assertTrue("Content", buffer.content[4] == 'o');
	}
	endTest();

	beginTest("Get end of buffer.");
	{
		Buffer buffer = bufferCreateFromString("hello");

		assertIntDecimal("Content", *(bufferEnd(&buffer) - 1), 'o');
	}
	endTest();

	beginTest("No length in common.");
	{
		Buffer a = bufferCreateFromString("hello");
		Buffer b = bufferCreateFromString("world");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b), 0);
	}
	endTest();

	beginTest("Beginning in common.");
	{
		Buffer a = bufferCreateFromString("ham");
		Buffer b = bufferCreateFromString("hamster");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b), 3);
	}
	endTest();

	beginTest("Partial in common.");
	{
		Buffer a = bufferCreateFromString("hammock");
		Buffer b = bufferCreateFromString("hamster");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b), 3);
	}
	endTest();
}
