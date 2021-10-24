#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

typedef struct CircularBuffer
{
	uint8_t values[0xff];
	uint8_t begin;
	uint8_t end;
} CircularBuffer;

void circularBufferInit(CircularBuffer *circularBuffer);
void circularBufferPush(CircularBuffer *circularBuffer, uint8_t value);
uint8_t circularBufferPop(CircularBuffer *circularBuffer);

#endif
