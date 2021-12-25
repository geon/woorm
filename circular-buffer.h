#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CircularBuffer
{
	uint8_t begin;
	uint8_t end;
} CircularBuffer;

void circularBufferInit(CircularBuffer *circularBuffer);
bool circularBufferPush(CircularBuffer *circularBuffer, uint8_t *index);
bool circularBufferPop(CircularBuffer *circularBuffer, uint8_t *index);
uint8_t circularBufferSize(CircularBuffer *circularBuffer);

#define circularBufferForEach(circularBuffer, iterator) for (iterator = circularBuffer->begin; iterator != circularBuffer->end; ++iterator)
#define circularBufferForEachReverse(circularBuffer, iterator) for (iterator = circularBuffer->end - 1; iterator != (uint8_t)(circularBuffer->begin - 1); --iterator)

#endif
