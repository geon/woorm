#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct Buffer
{
	uint8_t *content;
	size_t length;
	size_t capacity;
} Buffer;

Buffer bufferCreate(uint8_t *content, size_t length, size_t capacity);
Buffer bufferCreateFromString(char buffer[]);
uint8_t *bufferEnd(Buffer *buffer);
size_t bufferLengthInCommon(Buffer *a, Buffer *b, size_t maxLength);
bool bufferPush(Buffer *buffer, uint8_t value);

#endif
