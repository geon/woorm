#include "circular-buffer.h"

void circularBufferInit(uint8_t *circularBufferBegin, uint8_t *circularBufferEnd)
{
	*circularBufferBegin = 0;
	*circularBufferEnd = 0;
}

bool circularBufferPush(uint8_t circularBufferBegin, uint8_t *circularBufferEnd, uint8_t *index)
{
	if (circularBufferSize(circularBufferBegin, *circularBufferEnd) > 0xfe)
	{
		return false;
	}

	*index = *circularBufferEnd;
	++(*circularBufferEnd);
	return true;
}

bool circularBufferPop(uint8_t *circularBufferBegin, uint8_t circularBufferEnd, uint8_t *index)
{
	if (circularBufferSize(*circularBufferBegin, circularBufferEnd) == 0)
	{
		return false;
	}

	*index = *circularBufferBegin;
	++(*circularBufferBegin);
	return true;
}

uint8_t circularBufferSize(uint8_t circularBufferBegin, uint8_t circularBufferEnd)
{
	return circularBufferEnd - circularBufferBegin;
}
