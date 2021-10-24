#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

typedef struct CircularBuffer
{
    uint8_t placeholder;
} CircularBuffer;

void circularBufferInit(CircularBuffer *circularBuffer);

#endif
