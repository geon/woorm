#include "buffer.h"
#include "../cc65-test.h"
#include <string.h>

void bufferTest()
{
	beginTest("Create buffer.");
	{
		char string[] = "hello";
		Buffer buffer = bufferCreate((uint8_t *)string, 0, sizeof(string));

		assertIntDecimal("Length", buffer.length, 0);
		assertIntDecimal("Capacity", buffer.capacity, 6);
		assertTrue("Content", buffer.content == (uint8_t *)string);
	}
	endTest();

	beginTest("Create buffer from string.");
	{
		Buffer buffer = bufferCreateFromString("hello");

		assertIntDecimal("Length", buffer.length, 5);
		assertIntDecimal("Capacity", buffer.length, 5);
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

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b, 100), 0);
	}
	endTest();

	beginTest("Beginning in common.");
	{
		Buffer a = bufferCreateFromString("ham");
		Buffer b = bufferCreateFromString("hamster");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b, 100), 3);
	}
	endTest();

	beginTest("Partial in common.");
	{
		Buffer a = bufferCreateFromString("hammock");
		Buffer b = bufferCreateFromString("hamster");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b, 100), 3);
	}
	endTest();

	beginTest("Push to buffer.");
	{
		uint8_t content[4];
		Buffer buffer = bufferCreate(content, 0, sizeof(content));

		assertIntDecimal("Before", buffer.length, 0);
		bool success = bufferPush(&buffer, 'a');
		assertTrue("Success", success);
		assertIntDecimal("After", buffer.length, 1);
	}
	endTest();

	beginTest("Push past capacity.");
	{
		uint8_t content[1];
		Buffer buffer = bufferCreate(content, 1, sizeof(content));

		assertIntDecimal("Before", buffer.length, 1);
		bool success = bufferPush(&buffer, 'a');
		assertTrue("Fail", !success);
	}
	endTest();

	beginTest("No match past length.");
	{
		Buffer a = bufferCreateFromString("hamster");
		Buffer b = bufferCreateFromString("hamster");
		a.length = 3;

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b, 100), 3);
	}
	endTest();

	beginTest("Respect max length.");
	{
		Buffer a = bufferCreateFromString("hamster");
		Buffer b = bufferCreateFromString("hamster");

		assertIntDecimal("Common", bufferLengthInCommon(&a, &b, 3), 3);
	}
	endTest();
}
