#include "circular-buffer.h"
#include "cc65-test.h"

CircularBuffer circularBuffer;

void circularBufferTest()
{
	beginTest("Create circularBuffer.");
	{
		circularBufferInit(&circularBuffer);
	}
	endTest();

	beginTest("Push element to circularBuffer.");
	{
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, 0x12);
	}
	endTest();

	beginTest("Pop element from circularBuffer.");
	{
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, 0x12);
		circularBufferPop(&circularBuffer);
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
			circularBufferPush(&circularBuffer, pushed);
			popped = circularBufferPop(&circularBuffer);
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

		firstPushed = 0x12;
		secondPushed = 0x34;

		circularBufferPush(&circularBuffer, firstPushed);
		circularBufferPush(&circularBuffer, secondPushed);

		firstPopped = circularBufferPop(&circularBuffer);
		secondPopped = circularBufferPop(&circularBuffer);

		assertByte("First popped value should be the first pushed.", firstPopped, firstPushed);
		assertByte("Second popped value should be the second pushed.", secondPopped, secondPushed);
	}
	endTest();

	beginTest("Push/pop should in-/decrease size.");
	{
		circularBufferInit(&circularBuffer);
		assertByte("Fresh buffer should be empty.", circularBufferSize(&circularBuffer), 0);

		circularBufferPush(&circularBuffer, 0x12);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPush(&circularBuffer, 0x12);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 2);

		circularBufferPop(&circularBuffer);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPop(&circularBuffer);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 0);
	}
	endTest();

	beginTest("Push too many elements.");
	{
		uint16_t i;
		bool success;

		circularBufferInit(&circularBuffer);

		for (i = 0x00; i < 0xff; ++i)
		{
			success = circularBufferPush(&circularBuffer, 0x12);
			assertTrue("Should be able to push exactly 0xff - 1 bytes.", success);
		}

		success = circularBufferPush(&circularBuffer, 0x12);
		assertTrue("The buffer should be full now.", !success);
	}
	endTest();

	beginTest("Pop too many elements.");
	{
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, 0x12);
		circularBufferPop(&circularBuffer);
		assertByte("Should be back at zero size.", circularBufferSize(&circularBuffer), 0);
		circularBufferPop(&circularBuffer);
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
			circularBufferPush(&circularBuffer, 0);
			circularBufferPop(&circularBuffer);
		}

		// A few more pushes will bring it over the edge and loop back at the beginning.
		for (i = 0; i < 10; ++i)
		{
			pushed = i;
			circularBufferPush(&circularBuffer, pushed);
			popped = circularBufferPop(&circularBuffer);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Foreach should iterate the buffer.");
	{
		uint8_t pushed;
		uint8_t iterator;
		uint8_t value;
		uint8_t expected;
		uint16_t i;

		circularBufferInit(&circularBuffer);

		for (i = 0; i < 10; ++i)
		{
			pushed = i;
			circularBufferPush(&circularBuffer, pushed);
		}

		expected = 0;
		circularBufferForEach((&circularBuffer), iterator, value)
		{
			assertByte("Popped value should be same as pushed.", value, expected);
			++expected;
		}
	}
	endTest();

	beginTest("Foreach-reverse should iterate.");
	{
		uint8_t pushed;
		uint8_t iterator;
		uint8_t value;
		uint8_t expected;
		uint8_t count;
		uint16_t i;

		circularBufferInit(&circularBuffer);

		for (i = 0; i < 10; ++i)
		{
			pushed = i;
			circularBufferPush(&circularBuffer, pushed);
		}

		expected = pushed;
		count = 0;
		circularBufferForEachReverse((&circularBuffer), iterator, value)
		{
			assertByte("Value should be same as pushed.", value, expected);
			--expected;
			++count;
		}
		assertByte("All values should be iterated.", count, 10);
	}
	endTest();
}
