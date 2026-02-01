#include "circular-buffer.h"
#include "cc65-test.h"

CircularBuffer circularBuffer;
uint8_t circularBufferValues[0x100];

void circularBufferTest(void)
{
	beginTest("Create circularBuffer.");
	{
		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);
	}
	endTest();

	beginTest("Push element to circularBuffer.");
	{
		uint8_t foo = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
	}
	endTest();

	beginTest("Pop element from circularBuffer.");
	{
		uint8_t foo = 0;
		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &foo);
	}
	endTest();

	beginTest("Push and pop element.");
	{
		uint8_t popped = 0;
		uint8_t pushed = 0;
		uint16_t i = 0;

		// Can't for-loop over 256 element with a byte counter.
		for (i = 0x00; i <= 0xff; ++i)
		{
			pushed = (uint8_t)i;
			circularBufferInit(&circularBuffer.begin, &circularBuffer.end);
			circularBufferPush(circularBuffer.begin, &circularBuffer.end, &pushed);
			circularBufferPop(&circularBuffer.begin, circularBuffer.end, &popped);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Push and pop 2 elements.");
	{
		uint8_t firstPopped = 0;
		uint8_t secondPopped = 0;
		uint8_t firstPushed = 0;
		uint8_t secondPushed = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &firstPushed);
		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &secondPushed);

		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &firstPopped);
		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &secondPopped);

		assertByte("First popped value should be the first pushed.", firstPopped, firstPushed);
		assertByte("Second popped value should be the second pushed.", secondPopped, secondPushed);
	}
	endTest();

	beginTest("Push/pop should in-/decrease size.");
	{
		uint8_t foo = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);
		assertByte("Fresh buffer should be empty.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 0);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
		assertByte("Pushing should increase size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 1);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
		assertByte("Pushing should increase size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 2);

		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &foo);
		assertByte("Popping should decrease size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 1);

		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &foo);
		assertByte("Popping should decrease size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 0);
	}
	endTest();

	beginTest("Push too many elements.");
	{
		uint16_t i = 0;
		bool success = 0;
		uint8_t foo = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		for (i = 0x00; i < 0xff; ++i)
		{
			success = circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
			assertTrue("Should be able to push exactly 0xff - 1 bytes.", success);
		}

		success = circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
		assertTrue("The buffer should be full now.", !success);
	}
	endTest();

	beginTest("Pop too many elements.");
	{
		uint8_t foo = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		circularBufferPush(circularBuffer.begin, &circularBuffer.end, &foo);
		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &foo);
		assertByte("Should be back at zero size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 0);
		circularBufferPop(&circularBuffer.begin, circularBuffer.end, &foo);
		assertByte("Popping too many should not decrease size.", circularBufferSize(circularBuffer.begin, circularBuffer.end), 0);
	}
	endTest();

	beginTest("Push past the end, looping back.");
	{
		uint8_t popped = 0;
		uint8_t pushed = 0;
		uint16_t i = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		// Prep the buffer by pushing and popping to nearly capacity.
		for (i = 0; i < 250; ++i)
		{
			circularBufferPush(circularBuffer.begin, &circularBuffer.end, &pushed);
			circularBufferPop(&circularBuffer.begin, circularBuffer.end, &popped);
		}

		// A few more pushes will bring it over the edge and loop back at the beginning.
		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(circularBuffer.begin, &circularBuffer.end, &pushed);
			circularBufferPop(&circularBuffer.begin, circularBuffer.end, &popped);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Foreach should iterate the buffer.");
	{
		uint8_t pushed = 0;
		uint8_t iterator = 0;
		uint8_t expected = 0;
		uint16_t i = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(circularBuffer.begin, &circularBuffer.end, &pushed);
		}

		expected = 0;
		circularBufferForEach(circularBuffer.begin, circularBuffer.end, iterator)
		{
			assertByte("Popped value should be same as pushed.", iterator, expected);
			++expected;
		}
	}
	endTest();

	beginTest("Foreach-reverse should iterate.");
	{
		uint8_t pushed = 0;
		uint8_t iterator = 0;
		uint8_t expected = 0;
		uint8_t count = 0;
		uint16_t i = 0;

		circularBufferInit(&circularBuffer.begin, &circularBuffer.end);

		for (i = 0; i < 10; ++i)
		{
			circularBufferPush(circularBuffer.begin, &circularBuffer.end, &pushed);
		}

		expected = pushed;
		count = 0;
		circularBufferForEachReverse(circularBuffer.begin, circularBuffer.end, iterator)
		{
			assertByte("Value should be same as pushed.", iterator, expected);
			--expected;
			++count;
		}
		assertByte("All values should be iterated.", count, 10);
	}
	endTest();
}
