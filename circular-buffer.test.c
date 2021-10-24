#include "circular-buffer.h"
#include "cc65-test.h"

void circularBufferTest()
{
	beginTest("Create circularBuffer.");
	{
		CircularBuffer circularBuffer;
		circularBufferInit(&circularBuffer);
	}
	endTest();

	beginTest("Push element to circularBuffer.");
	{
		CircularBuffer circularBuffer;
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, 0x12);
	}
	endTest();

	beginTest("Pop element from circularBuffer.");
	{
		CircularBuffer circularBuffer;
		circularBufferInit(&circularBuffer);

		circularBufferPush(&circularBuffer, 0x12);
		circularBufferPop(&circularBuffer);
	}
	endTest();
}
