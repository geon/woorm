#include "circular-buffer.h"

void circularBufferInit(CircularBuffer *circularBuffer)
{
	circularBuffer->begin = 0;
	circularBuffer->end = 0;
}

bool circularBufferPush(CircularBuffer *circularBuffer, uint8_t value)
{
	if (circularBufferSize(circularBuffer) > 0xfe)
	{
		return false;
	}

	circularBuffer->values[circularBuffer->end] = value;
	++(circularBuffer->end);
	return true;
}

bool circularBufferPop(CircularBuffer *circularBuffer, uint8_t *value)
{
	if (circularBufferSize(circularBuffer) == 0)
	{
		return false;
	}

	*value = circularBuffer->values[circularBuffer->begin];
	++(circularBuffer->begin);
	return true;
}

uint8_t circularBufferSize(CircularBuffer *circularBuffer)
{
	return circularBuffer->end - circularBuffer->begin;
}
