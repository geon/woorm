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

		backReferenceEncodeToBuffer(&backReference, &buffer);

		assertIntDecimal("Buffer length", buffer.length, 2);
		assertIntDecimal("Byte 1", buffer.content[0], 0b11111111);
		assertIntDecimal("Byte 2", buffer.content[1], 0b11111111);
	}
	endTest();

	beginTest("Decode back-reference.");
	{
		uint8_t content[] = {0b11111111, 0b11111111};
		Buffer buffer = bufferCreate(content, 2, sizeof(content));

		BackReference decoded = backReferenceDecodeFromBuffer(&buffer);

		assertIntDecimal("Distance", decoded.distance, BACK_REFERENCE_DISTANCE_BIT_MASK);
		assertIntDecimal("Length", decoded.length, BACK_REFERENCE_LENGTH_BIT_MASK);
	}
	endTest();

	beginTest("Encode/decode back-reference.");
	{
		BackReference backReference = backReferenceCreate(
			999,
			49);

		uint8_t content[2];
		Buffer buffer = bufferCreate(content, 0, sizeof(content));

		backReferenceEncodeToBuffer(&backReference, &buffer);

		assertIntDecimal("Buffer length", buffer.length, 2);

		BackReference decoded = backReferenceDecodeFromBuffer(&buffer);

		assertIntDecimal("Distance", decoded.distance, backReference.distance);
		assertIntDecimal("Length", decoded.length, backReference.length);
	}
	endTest();

	beginTest("Find back-reference.");
	{
		Buffer buffer = bufferCreateFromString("hamster ham");

		BackReference backReference = backReferenceFind(&buffer, 8);

		assertIntDecimal("Length", backReference.length, 3);
		assertIntDecimal("Distance", backReference.distance, 8);
	}
	endTest();

	beginTest("No back-reference.");
	{
		Buffer buffer = bufferCreateFromString("ab");

		BackReference backReference = backReferenceFind(&buffer, 1);

		assertIntDecimal("Length", backReference.length, 0);
		assertIntDecimal("Distance", backReference.distance, 0);
	}
	endTest();
}
