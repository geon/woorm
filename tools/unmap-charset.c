#include "../tile.h"
#include "charset.h"
#include "partial-charset.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void mappingTablePrint(FILE *f, uint8_t mappingTable[0x100])
{
	fprintf(f, "#include <stdint.h>\n\n");
	fprintf(f, "uint8_t tileToIndex[256] =");
	fprintf(f, "\n{\n");
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			fprintf(f, "0x%.2X", mappingTable[i * 16 + j]);
			if (i < 16 - 1 || j < 16 - 1)
			{
				fprintf(f, ", ");
			}
		}
		fprintf(f, "\n");
	}
	fprintf(f, "};\n");
}

void charsetPrint(FILE *f, Charset charset)
{
	fprintf(f, ".segment \"CHARSET\"\n.export _wormCharset\n_wormCharset:\n");
	for (int i = 0; i < 256; ++i)
	{
		fprintf(
			f,
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

void unmapCharset(PartialCharset *newCharset, uint8_t *mappingTable, Charset originalWormCharset)
{

	CharsetChar blank = {0, 0, 0, 0, 0, 0, 0, 0};
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

	newCharset->numUsedChars = 0;
	// Index 0 is special and must be preserved.
	++newCharset->numUsedChars;
	for (int i = 0; i < 0x100; ++i)
	{
		charsetCharCopy(blank, newCharset->charset[i]);
	}

	partialCharsetCompress(newCharset, cleanedWormCharset, mappingTable);
}

extern Charset originalWormCharset;

int main()
{
	PartialCharset newCharset;
	uint8_t mappingTable[256];
	unmapCharset(&newCharset, mappingTable, originalWormCharset);

	FILE *tileMappingFile = fopen("../tile-to-index.c", "w");
	if (tileMappingFile == NULL)
	{
		printf("Error opening tile-to-index.c!\n");
		exit(1);
	}

	mappingTablePrint(tileMappingFile, mappingTable);

	FILE *charsetFile = fopen("../worm-charset.asm", "w");
	if (charsetFile == NULL)
	{
		printf("Error opening worm-charset.asm!\n");
		exit(1);
	}

	charsetPrint(charsetFile, newCharset.charset);

	return 0;
}
