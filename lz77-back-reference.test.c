#include "lz77-back-reference.h"
#include "cc65-test.h"
#include "lz77-back-reference.test.h"
#include <string.h>

void lz77BackReferenceTest()
{
	beginTest("Encode back-reference.");
	{
		// Use the entire capacity of the back reference.
		BackReference backReference;
		uint8_t a, b;

		backReference = backReferenceCreate(
			BACK_REFERENCE_DISTANCE_BIT_MASK,
			BACK_REFERENCE_LENGTH_BIT_MASK);

		backReferenceEncodeToBytes(&backReference, &a, &b);

		assertIntDecimal("Byte a", a, 0b11111111);
		assertIntDecimal("Byte b", b, 0b11111111);
	}
	endTest();

	beginTest("Decode back-reference.");
	{
		uint8_t a = 0b11111111;
		uint8_t b = 0b11111111;
		BackReference decoded;

		decoded = backReferenceDecodeFromBytes(a, b);

		assertIntDecimal("Distance", decoded.distance, BACK_REFERENCE_DISTANCE_BIT_MASK);
		assertIntDecimal("Length", decoded.length, BACK_REFERENCE_LENGTH_BIT_MASK);
	}
	endTest();

	beginTest("Encode/decode back-reference.");
	{
		BackReference backReference;
		BackReference decoded;
		uint8_t a, b;

		backReference = backReferenceCreate(
			999,
			49);

		backReferenceEncodeToBytes(&backReference, &a, &b);
		decoded = backReferenceDecodeFromBytes(a, b);

		assertIntDecimal("Distance", decoded.distance, backReference.distance);
		assertIntDecimal("Length", decoded.length, backReference.length);
	}
	endTest();
}
