#include "buffer.h"
#include <string.h>

Buffer bufferCreate(uint8_t *content, size_t length)
{
	Buffer buffer;
	buffer.content = content;
	buffer.length = length;
	return buffer;
}

Buffer bufferCreateFromString(char string[])
{
	Buffer buffer;
	buffer.content = (uint8_t *)string;
	buffer.length = strlen(string);
	return buffer;
}
