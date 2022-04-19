#include "buffer.h"
#include <string.h>

Buffer bufferCreate(uint8_t *content, size_t length, size_t capacity)
{
	Buffer buffer;
	buffer.content = content;
	buffer.length = length;
	buffer.capacity = capacity;
	return buffer;
}

Buffer bufferCreateFromString(char string[])
{
	Buffer buffer;
	buffer.content = (uint8_t *)string;
	buffer.length = strlen(string);
	return buffer;
}

uint8_t *bufferEnd(Buffer *buffer)
{
	return buffer->content + buffer->length;
}

size_t bufferLengthInCommon(Buffer *a, Buffer *b)
{
	int length;
	for (
		length = 0;

		length <= a->length &&
		length <= b->length;

		++length)
	{
		if (
			a->content[length] !=
			b->content[length])
		{
			break;
		}
	}
	return length;
}

bool bufferPush(Buffer *buffer, uint8_t value)
{
	if (buffer->length >= buffer->capacity)
	{
		return false;
	}

	buffer->content[buffer->length] = value;
	++(buffer->length);
	return true;
}
