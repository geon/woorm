#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct Buffer
{
	uint8_t *content;
	size_t length;
} Buffer;

Buffer bufferCreate(uint8_t *content, size_t length);
Buffer bufferCreateFromString(char buffer[]);
uint8_t *bufferEnd(Buffer *buffer);

#endif
