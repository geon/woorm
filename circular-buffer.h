#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CircularBuffer
{
	uint8_t values[0x100];
	uint8_t begin;
	uint8_t end;
} CircularBuffer;

void circularBufferInit(CircularBuffer *circularBuffer);
bool circularBufferPush(CircularBuffer *circularBuffer, uint8_t value);
uint8_t circularBufferPop(CircularBuffer *circularBuffer);
uint8_t circularBufferSize(CircularBuffer *circularBuffer);

#define circularBufferForEach(circularBuffer, iterator, value) for (iterator = circularBuffer->begin; value = circularBuffer->values[iterator], iterator != circularBuffer->end; ++iterator)
#define circularBufferForEachReverse(circularBuffer, iterator, value) for (iterator = circularBuffer->end - 1; value = circularBuffer->values[iterator], iterator != (uint8_t)(circularBuffer->begin - 1); --iterator)

#endif
