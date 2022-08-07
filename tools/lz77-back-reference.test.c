#include "lz77-back-reference.h"
#include "../cc65-test.h"
#include <string.h>

void lz77backReferenceTest()
{
	beginTest("Encode back-reference.");
	{
		// Use the entire capacity of the back reference.
		BackReference backReference = backReferenceCreate(
			BACK_REFERENCE_DISTANCE_BIT_MASK,
			BACK_REFERENCE_LENGTH_BIT_MASK);

		uint8_t content[2];
		Buffer buffer = bufferCreate(content, 0, sizeof(content));

		backReferenceEncode(&backReference, &buffer);

		assertIntDecimal("Buffer length", buffer.length, 2);
		assertIntDecimal("Byte 1", buffer.content[0], 0b11111111);
		assertIntDecimal("Byte 2", buffer.content[1], 0b11111111);
	}
	endTest();
}
