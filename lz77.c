#include "lz77.h"
#include <stdbool.h>

BackReference backReferenceDecode(uint8_t a, uint8_t b)
{
	BackReference backReference;
	backReference.distance =
		(a << (BACK_REFERENCE_DISTANCE_NUM_BITS - 8)) |
		((b & ~BACK_REFERENCE_LENGTH_BIT_MASK) >> (BACK_REFERENCE_LENGTH_NUM_BITS));
	backReference.length = b & BACK_REFERENCE_LENGTH_BIT_MASK;
	return backReference;
}

void lz77Decompress(
	uint8_t compressed[], int compressedBufferSize,
	uint8_t decompressed[], int decompressedBufferSize)
{
	uint8_t *read = compressed;
	uint8_t *write = decompressed;

	// Alternate reading raw bytes and back-references.
	while (true)
	{
		// Start with reading a raw byte.
		*(write++) = *(read++);

		// Check if done.
		if (write >= decompressed + decompressedBufferSize || read >= compressed + compressedBufferSize)
		{
			break;
		}

		{
			uint8_t a, b;
			BackReference backReference;
			uint8_t *backRead;

			// Read a back-reference.
			a = *(read++);
			b = *(read++);
			backReference = backReferenceDecode(a, b);

			// Copy back-reference from DEcompressed back to DEcompressed.
			backRead = write - backReference.distance;
			{
				uint16_t i;
				for (i = 0; i < backReference.length; ++i)
				{
					*(write++) = *(backRead++);
				}
			}

			// Check if done.
			if (write >= decompressed + decompressedBufferSize || read >= compressed + compressedBufferSize)
			{
				break;
			}
		}
	}
}
