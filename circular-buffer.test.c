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
}
