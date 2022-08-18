#include "lz77.h"
#include "lz77-back-reference.h"

void lz77Compress(Buffer *uncompressed, Buffer *compressed)
{
	uint8_t *read = uncompressed->content;

	// Alternate writing raw bytes and back-references.
	while (true)
	{
		// Start with writing a raw byte.
		bufferPush(compressed, *(read++));

		// Check if done.
		if (compressed->length >= compressed->capacity || read >= bufferEnd(uncompressed))
		{
			break;
		}

		// Write a back-reference.
		BackReference backReference = backReferenceFind(uncompressed, read - uncompressed->content);
		backReferenceEncode(&backReference, compressed);
		read += backReference.length;

		// Check if done.
		if (compressed->length >= compressed->capacity || read >= bufferEnd(uncompressed))
		{
			break;
		}
	}
}

void lz77Decompress(Buffer *compressed, Buffer *decompressed)
{

	uint8_t *read = compressed->content;

	// Alternate reading raw bytes and back-references.
	while (true)
	{
		// Start with reading a raw byte.
		bufferPush(decompressed, *(read++));

		// Check if done.
		if (decompressed->length >= decompressed->capacity || read >= bufferEnd(compressed))
		{
			break;
		}

		// Read a back-reference.
		Buffer partial = bufferCreate(read, compressed->length - (read - compressed->content), compressed->length - (read - compressed->content));
		BackReference backReference = backReferenceDecodeFromBuffer(&partial);

		// Copy back-reference from DEcompressed back to DEcompressed.
		uint8_t *backRead = bufferEnd(decompressed) - backReference.distance;
		for (int i = 0; i < backReference.length; ++i)
		{
			bufferPush(decompressed, *(backRead++));
		}
		read += 2;

		// Check if done.
		if (decompressed->length >= decompressed->capacity || read >= bufferEnd(compressed))
		{
			break;
		}
	}
}
