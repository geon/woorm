#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CircularBuffer
{
	uint8_t begin;
	uint8_t end;
} CircularBuffer;

void circularBufferInit(uint8_t *circularBufferBegin, uint8_t *circularBufferEnd);
bool circularBufferPush(uint8_t circularBufferBegin, uint8_t *circularBufferEnd, uint8_t *index);
bool circularBufferPop(uint8_t *circularBufferBegin, uint8_t circularBufferEnd, uint8_t *index);
uint8_t circularBufferSize(uint8_t circularBufferBegin, uint8_t circularBufferEnd);

#define circularBufferForEach(circularBufferBegin, circularBufferEnd, iterator) for (iterator = circularBufferBegin; iterator != circularBufferEnd; ++iterator)
#define circularBufferForEachReverse(circularBufferBegin, circularBufferEnd, iterator) for (iterator = circularBufferEnd - 1; iterator != (uint8_t)(circularBufferBegin - 1); --iterator)

#endif
