#include "lz77-back-reference.h"

BackReference backReferenceCreate(uint16_t distance, uint16_t length)
{
	BackReference backReference;
	backReference.distance = distance;
	backReference.length = length;
	return backReference;
}

void backReferenceEncodeToBytes(BackReference *backReference, uint8_t *a, uint8_t *b)
{
	*a = (uint8_t)(backReference->distance >> (BACK_REFERENCE_DISTANCE_NUM_BITS - 8));
	*b = (uint8_t)((backReference->distance << BACK_REFERENCE_LENGTH_NUM_BITS) |
				   (backReference->length & BACK_REFERENCE_LENGTH_BIT_MASK));
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
