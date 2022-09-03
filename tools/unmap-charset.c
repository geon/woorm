#include "../tile.h"
#include "charset.h"
#include "partial-charset.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void mappingTablePrint(uint8_t mappingTable[0x100])
{
	printf("#include <stdint.h>\n\n");
	printf("uint8_t tileToIndex[256] =");
	printf("\n{\n");
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			printf("0x%.2X", mappingTable[i * 16 + j]);
			if (i < 16 - 1 || j < 16 - 1)
			{
				printf(", ");
			}
		}
		printf("\n");
	}
	printf("};\n");
}

void charsetPrint(Charset charset)
{
	printf(".segment \"CHARSET\"\n.export _wormCharset\n_wormCharset:\n");
	for (int i = 0; i < 256; ++i)
	{
		printf(
			".byte $%.2X, $%.2X, $%.2X, $%.2X, $%.2X, $%.2X, $%.2X, $%.2X\n",
			charset[i][0],
			charset[i][1],
			charset[i][2],
			charset[i][3],
			charset[i][4],
			charset[i][5],
			charset[i][6],
			charset[i][7]);
	}
}

extern Charset originalWormCharset;

int main()
{
	CharsetChar blank = {0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t mappingTable[256];
	Charset cleanedWormCharset;
	for (int i = 0; i < 0x100; ++i)
	{
		charsetCharCopy(blank, cleanedWormCharset[i]);
	}

	for (int i = 0; i < 7; ++i)
	{
		charsetCharCopy(originalWormCharset[i], cleanedWormCharset[i]);
	}

	for (TileType tileType = TileType_animated_head; tileType <= TileType_animated_end; ++tileType)
		for (Direction direction = Direction_first; direction < Direction_count; ++direction)
			for (Microstep step = Microstep_0; step <= Microstep_3; step += 4)
			{
				{
					Direction nextDirection = direction;
					uint8_t sourceIndex = tileCreate(tileType, direction, nextDirection, step);
					uint8_t tileBits = tilePackWormTileStateInBits(tileType, direction, nextDirection, step);
					charsetCharCopy(originalWormCharset[sourceIndex], cleanedWormCharset[tileBits]);
				}

				{
					Direction nextDirection = (direction + 1) & 3;
					uint8_t sourceIndex = tileCreate(tileType, direction, nextDirection, step);
					uint8_t tileBits = tilePackWormTileStateInBits(tileType, direction, nextDirection, step);
					charsetCharCopy(originalWormCharset[sourceIndex], cleanedWormCharset[tileBits]);
				}

				{
					Direction nextDirection = (direction + 3) & 3;
					uint8_t sourceIndex = tileCreate(tileType, direction, nextDirection, step);
					uint8_t tileBits = tilePackWormTileStateInBits(tileType, direction, nextDirection, step);
					charsetCharCopy(originalWormCharset[sourceIndex], cleanedWormCharset[tileBits]);
				}
			}

	PartialCharset newCharset;
	newCharset.numUsedChars = 0;
	// Index 0 is special and must be preserved.
	charsetCharCopy(originalWormCharset[0], newCharset.charset[0]);
	++newCharset.numUsedChars;
	for (int i = 0; i < 0x100; ++i)
	{
		charsetCharCopy(blank, newCharset.charset[i]);
	}

	partialCharsetCompress(&newCharset, cleanedWormCharset, mappingTable);

	mappingTablePrint(mappingTable);

	charsetPrint(newCharset.charset);

	return 0;
}
