#include "lz77-back-reference.h"

BackReference backReferenceCreate(size_t distance, size_t length)
{
	BackReference backReference;
	backReference.distance = distance;
	backReference.length = length;
	return backReference;
}

void backReferenceEncode(BackReference *backReference, Buffer *buffer)
{
	uint8_t a, b;
	a = (uint8_t)(backReference->distance >> (BACK_REFERENCE_DISTANCE_NUM_BITS - 8));
	b = (uint8_t)((backReference->distance << BACK_REFERENCE_LENGTH_NUM_BITS) |
				  (backReference->length & BACK_REFERENCE_LENGTH_BIT_MASK));
	bufferPush(buffer, a);
	bufferPush(buffer, b);
}

BackReference backReferenceDecodeFromBytes(uint8_t a, uint8_t b)
{
	BackReference backReference;
	backReference.distance =
		(a << (BACK_REFERENCE_DISTANCE_NUM_BITS - 8)) |
		((b & ~BACK_REFERENCE_LENGTH_BIT_MASK) >> (BACK_REFERENCE_LENGTH_NUM_BITS));
	backReference.length = b & BACK_REFERENCE_LENGTH_BIT_MASK;
	return backReference;
}

BackReference backReferenceDecodeFromBuffer(Buffer *buffer)
{
	uint8_t a, b;
	a = buffer->content[0];
	b = buffer->content[1];
	return backReferenceDecodeFromBytes(a, b);
}

BackReference backReferenceFind(Buffer *buffer, size_t location)
{
	BackReference backReference = backReferenceCreate(0, 0);

	Buffer needle;
	needle.content = buffer->content + location;
	needle.length = buffer->length - location;

	for (int distance = 1; distance <= location && distance <= BACK_REFERENCE_DISTANCE_BIT_MASK; ++distance)
	{
		Buffer haystack;
		haystack.content = buffer->content + (location - distance);
		haystack.length = buffer->length - (location - distance);

		size_t length = bufferLengthInCommon(&haystack, &needle);
		if (length > backReference.length)
		{
			backReference.length = length;
			backReference.distance = distance;
		}
	}

	return backReference;
}