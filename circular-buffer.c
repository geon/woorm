#include "circular-buffer.h"

void circularBufferInit(CircularBuffer *circularBuffer)
{
	circularBuffer->begin = 0;
	circularBuffer->end = 0;
}

void circularBufferPush(CircularBuffer *circularBuffer, uint8_t value)
{
	circularBuffer->values[circularBuffer->end] = value;
	++(circularBuffer->end);
}

uint8_t circularBufferPop(CircularBuffer *circularBuffer)
{
	uint8_t value = circularBuffer->values[circularBuffer->begin];
	++(circularBuffer->begin);
	return value;
}
