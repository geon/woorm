#ifndef LZ77_BACK_REFERENCE_H
#define LZ77_BACK_REFERENCE_H

#include <stdint.h>

// The back references are encoded in 16 bits, with 10 bits for the distance, and 6 bits for the length.
#define BACK_REFERENCE_DISTANCE_NUM_BITS 10
#define BACK_REFERENCE_LENGTH_NUM_BITS (16 - BACK_REFERENCE_DISTANCE_NUM_BITS)
// Masks for the distance and length, respectively.
#define BACK_REFERENCE_DISTANCE_BIT_MASK ((1 << BACK_REFERENCE_DISTANCE_NUM_BITS) - 1)
#define BACK_REFERENCE_LENGTH_BIT_MASK ((1 << BACK_REFERENCE_LENGTH_NUM_BITS) - 1)

typedef struct BackReference
{
	uint16_t distance;
	uint16_t length;
} BackReference;

BackReference backReferenceCreate(uint16_t distance, uint16_t length);
void backReferenceEncodeToBytes(BackReference *backReference, uint8_t *a, uint8_t *b);
BackReference backReferenceDecodeFromBytes(uint8_t a, uint8_t b);

#endif
