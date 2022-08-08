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
