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
