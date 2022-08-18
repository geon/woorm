#include "lz77.h"
#include "../cc65-test.h"
#include "buffer.h"
#include <string.h>

void lz77Test()
{
	beginTest("No match.");
	{
		Buffer original = bufferCreateFromString("ab");
		uint8_t content[8];
		Buffer compressed = bufferCreate(content, 0, sizeof(content));

		lz77Compress(&original, &compressed);

		assertIntDecimal("Length", compressed.length, 4);
		assertIntDecimal("content[0]", compressed.content[0], 'a');
		assertIntDecimal("content[1]", compressed.content[1], 0);
		assertIntDecimal("content[2]", compressed.content[2], 0);
		assertIntDecimal("content[3]", compressed.content[3], 'b');
	}
	endTest();

	beginTest("Match.");
	{
		Buffer original = bufferCreateFromString("abab");
		uint8_t content[16];
		Buffer compressed = bufferCreate(content, 0, sizeof(content));

		lz77Compress(&original, &compressed);

		assertIntDecimal("Length", compressed.length, 6);
		assertIntDecimal("content[0]", compressed.content[0], 'a');
		assertIntDecimal("content[1]", compressed.content[1], 0);
		assertIntDecimal("content[2]", compressed.content[2], 0);
		assertIntDecimal("content[3]", compressed.content[3], 'b');
		assertIntDecimal("content[4]", compressed.content[4], 0b00000000);
		assertIntDecimal("content[5]", compressed.content[5], 0b10000010);
	}
	endTest();

	beginTest("Matches.");
	{
		Buffer original = bufferCreateFromString("to be or not to be");
		uint8_t content[100];
		Buffer compressed = bufferCreate(content, 0, sizeof(content));

		lz77Compress(&original, &compressed);

		assertIntDecimal("Length", compressed.length, 30);
		assertIntDecimal("content[0]", compressed.content[0], 't');
		assertIntDecimal("content[1]", compressed.content[1], 0);
		assertIntDecimal("content[2]", compressed.content[2], 0);
		assertIntDecimal("content[3]", compressed.content[3], 'o');
		assertIntDecimal("content[4]", compressed.content[4], 0);
		assertIntDecimal("content[5]", compressed.content[5], 0);
		assertIntDecimal("content[6]", compressed.content[6], ' ');
		assertIntDecimal("content[7]", compressed.content[7], 0);
		assertIntDecimal("content[8]", compressed.content[8], 0);
		assertIntDecimal("content[9]", compressed.content[9], 'b');
		assertIntDecimal("content[10]", compressed.content[10], 0);
		assertIntDecimal("content[11]", compressed.content[11], 0);
		assertIntDecimal("content[12]", compressed.content[12], 'e');
		assertIntDecimal("content[13]", compressed.content[13], 0b00000000);
		assertIntDecimal("content[14]", compressed.content[14], 0b11000001);
		assertIntDecimal("content[15]", compressed.content[15], 'o');
		assertIntDecimal("content[16]", compressed.content[16], 0);
		assertIntDecimal("content[17]", compressed.content[17], 0);
		assertIntDecimal("content[18]", compressed.content[18], 'r');
		assertIntDecimal("content[19]", compressed.content[19], 0b00000000);
		assertIntDecimal("content[20]", compressed.content[20], 0b11000001);
		assertIntDecimal("content[21]", compressed.content[21], 'n');
		assertIntDecimal("content[22]", compressed.content[22], 0b00000001);
		assertIntDecimal("content[23]", compressed.content[23], 0b00000001);
		assertIntDecimal("content[24]", compressed.content[24], 't');
		assertIntDecimal("content[25]", compressed.content[25], 0b00000001);
		assertIntDecimal("content[26]", compressed.content[26], 0b00000001);
		assertIntDecimal("content[27]", compressed.content[27], 't');
		assertIntDecimal("content[28]", compressed.content[28], 0b00000011);
		assertIntDecimal("content[29]", compressed.content[29], 0b01000100);
	}
	endTest();

	beginTest("Decompress.");
	{
		Buffer original = bufferCreateFromString("Far, får får får? Nej, får får inte får, får får lamm.");

		uint8_t compressedContent[100];
		Buffer compressed = bufferCreate(compressedContent, 0, sizeof(compressedContent));

		uint8_t decompressedContent[100];
		Buffer decompressed = bufferCreate(decompressedContent, 0, sizeof(decompressedContent));

		lz77Compress(&original, &compressed);
		lz77Decompress(&compressed, &decompressed);

		assertIntDecimal("Length", decompressed.length, original.length);
		for (size_t i = 0; i < decompressed.length; ++i)
		{
			assertIntDecimal("content", decompressed.content[i], original.content[i]);
		}
	}
	endTest();
}
