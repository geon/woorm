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

BackReference backReferenceDecode(Buffer *buffer)
{
	uint8_t a, b;
	a = buffer->content[0];
	b = buffer->content[1];

	BackReference backReference;
	backReference.distance =
		(a << (BACK_REFERENCE_DISTANCE_NUM_BITS - 8)) |
		((b & ~BACK_REFERENCE_LENGTH_BIT_MASK) >> (BACK_REFERENCE_LENGTH_NUM_BITS));
	backReference.length = b & BACK_REFERENCE_LENGTH_BIT_MASK;
	return backReference;
}
