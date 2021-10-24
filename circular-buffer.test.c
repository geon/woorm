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
}
