#include "lz77-back-reference.tools.h"

void backReferenceEncodeToBuffer(BackReference *backReference, Buffer *buffer)
{
	uint8_t a, b;
	backReferenceEncodeToBytes(backReference, &a, &b);
	bufferPush(buffer, a);
	bufferPush(buffer, b);
}

BackReference backReferenceDecodeFromBuffer(Buffer *buffer)
{
	uint8_t a, b;
	a = buffer->content[0];
	b = buffer->content[1];
	return backReferenceDecodeFromBytes(a, b);
}

BackReference backReferenceFind(Buffer *buffer, uint16_t location)
{
	BackReference backReference = backReferenceCreate(0, 0);

	Buffer needle;
	needle.content = buffer->content + location;
	needle.length = buffer->length - location;

	for (uint16_t distance = 1; distance <= location && distance <= BACK_REFERENCE_DISTANCE_BIT_MASK; ++distance)
	{
		Buffer haystack;
		haystack.content = buffer->content + (location - distance);
		haystack.length = buffer->length - (location - distance);

		uint16_t length = (uint16_t)bufferLengthInCommon(&haystack, &needle);
		if (length > backReference.length)
		{
			backReference.length = length;
			backReference.distance = distance;
		}
	}

	return backReference;
}