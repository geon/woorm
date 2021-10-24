#include "circular-buffer.h"

void circularBufferInit(CircularBuffer *circularBuffer)
{
}

void circularBufferPush(CircularBuffer *circularBuffer, uint8_t value)
{
	circularBuffer->value = value;
}

uint8_t circularBufferPop(CircularBuffer *circularBuffer)
{
	return circularBuffer->value;
}
