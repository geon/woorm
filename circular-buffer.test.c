#include "circular-buffer.h"
#include "cc65-test.h"

CircularBuffer circularBuffer;
uint8_t circularBufferValues[0x100];

void circularBufferTest()
{
	beginTest("Create circularBuffer.");
	{
		circularBufferInit(&circularBuffer);
	}
	endTest();

	beginTest("Push element to circularBuffer.");
	{
		uint8_t foo;

		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, &foo);
	}
	endTest();

	beginTest("Pop element from circularBuffer.");
	{
		uint8_t foo;
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, &foo);
		circularBufferPop(&circularBuffer, &foo);
	}
	endTest();

	beginTest("Push and pop element.");
	{
		uint8_t popped;
		uint8_t pushed;
		uint16_t i;

		// Can't for-loop over 256 element with a byte counter.
		for (i = 0x00; i <= 0xff; ++i)
		{
			pushed = i;
			circularBufferInit(&circularBuffer);
			circularBufferPush(&circularBuffer, &pushed);
			circularBufferPop(&circularBuffer, &popped);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Push and pop 2 elements.");
	{
		uint8_t firstPopped;
		uint8_t secondPopped;
		uint8_t firstPushed;
		uint8_t secondPushed;

		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, &firstPushed);
		circularBufferPush(&circularBuffer, &secondPushed);

		circularBufferPop(&circularBuffer, &firstPopped);
		circularBufferPop(&circularBuffer, &secondPopped);

		assertByte("First popped value should be the first pushed.", firstPopped, firstPushed);
		assertByte("Second popped value should be the second pushed.", secondPopped, secondPushed);
	}
	endTest();

	beginTest("Push/pop should in-/decrease size.");
	{
		uint8_t foo;

		circularBufferInit(&circularBuffer);
		assertByte("Fresh buffer should be empty.", circularBufferSize(&circularBuffer), 0);

		circularBufferPush(&circularBuffer, &foo);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPush(&circularBuffer, &foo);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 2);

		circularBufferPop(&circularBuffer, &foo);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPop(&circularBuffer, &foo);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 0);
	}
	endTest();

	beginTest("Push too many elements.");
	{
		uint16_t i;
		bool success;
		uint8_t foo;

		circularBufferInit(&circularBuffer);

		for (i = 0x00; i < 0xff; ++i)
		{
			success = circularBufferPush(&circularBuffer, &foo);
			assertTrue("Should be able to push exactly 0xff - 1 bytes.", success);
		}

		success = circularBufferPush(&circularBuffer, &foo);
		assertTrue("The buffer should be full now.", !success);
	}
	endTest();

	beginTest("Pop too many elements.");
	{
		uint8_t foo;

		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, &foo);
		circularBufferPop(&circularBuffer, &foo);
		assertByte("Should be back at zero size.", circularBufferSize(&circularBuffer), 0);
		circularBufferPop(&circularBuffer, &foo);
		assertByte("Popping too many should not decrease size.", circularBufferSize(&circularBuffer), 0);
	}
	endTest();

	beginTest("Push past the end, looping back.");
	{
		uint8_t popped;
		uint8_t pushed;
		uint16_t i;

		circularBufferInit(&circularBuffer);

		// Prep the buffer by pushing and popping to nearly capacity.
		for (i = 0; i < 250; ++i)
		{
			circularBufferPush(&circularBuffer, &pushed);
			circularBufferPop(&circularBuffer, &popped);
		}

		// A few more pushes will bring it over the edge and loop back at the beginning.
		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(&circularBuffer, &pushed);
			circularBufferPop(&circularBuffer, &popped);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Foreach should iterate the buffer.");
	{
		uint8_t pushed;
		uint8_t iterator;
		uint8_t expected;
		uint16_t i;

		circularBufferInit(&circularBuffer);

		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(&circularBuffer, &pushed);
		}

		expected = 0;
		circularBufferForEach((&circularBuffer), iterator)
		{
			assertByte("Popped value should be same as pushed.", iterator, expected);
			++expected;
		}
	}
	endTest();

	beginTest("Foreach-reverse should iterate.");
	{
		uint8_t pushed;
		uint8_t iterator;
		uint8_t expected;
		uint8_t count;
		uint16_t i;

		circularBufferInit(&circularBuffer);

		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(&circularBuffer, &pushed);
		}

		expected = pushed;
		count = 0;
		circularBufferForEachReverse((&circularBuffer), iterator)
		{
			assertByte("Value should be same as pushed.", iterator, expected);
			--expected;
			++count;
		}
		assertByte("All values should be iterated.", count, 10);
	}
	endTest();
}
