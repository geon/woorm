#include "buffer.h"

Buffer bufferCreate(uint8_t *content, size_t length)
{
	Buffer buffer;
	buffer.content = content;
	buffer.length = length;
	return buffer;
}
