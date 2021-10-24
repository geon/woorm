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
}
