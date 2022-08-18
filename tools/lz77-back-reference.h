#ifndef LZ77_BACK_REFERENCE_H
#define LZ77_BACK_REFERENCE_H

#include "buffer.h"
#include <stddef.h>

// The back references are encoded in 16 bits, with 10 bits for the distance, and 6 bits for the length.
#define BACK_REFERENCE_DISTANCE_NUM_BITS 10
#define BACK_REFERENCE_LENGTH_NUM_BITS (16 - BACK_REFERENCE_DISTANCE_NUM_BITS)
// Masks for the distance and length, respectively.
#define BACK_REFERENCE_DISTANCE_BIT_MASK ((1 << BACK_REFERENCE_DISTANCE_NUM_BITS) - 1)
#define BACK_REFERENCE_LENGTH_BIT_MASK ((1 << BACK_REFERENCE_LENGTH_NUM_BITS) - 1)

typedef struct BackReference
{
	size_t distance;
	size_t length;
} BackReference;

BackReference backReferenceCreate(size_t distance, size_t length);
void backReferenceEncode(BackReference *backReference, Buffer *buffer);
BackReference backReferenceDecodeFromBytes(uint8_t a, uint8_t b);
BackReference backReferenceDecodeFromBuffer(Buffer *buffer);
BackReference backReferenceFind(Buffer *buffer, size_t location);

#endif
