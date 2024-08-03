#include "../tile.h"
#include "buffer.h"
#include "charset.h"
#include "level.h"
#include "lz77.h"
#include "partial-charset.h"
#include "tile.legacy.h"
#include "uncompressed-levels.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

	// Clear the `newCharset`.
	newCharset->numUsedChars = 0;
	for (int i = 0; i < 0x100; ++i)
	{
		charsetCharCopy(blank, newCharset->charset[i]);
	}

	// Index 0 is special and must be preserved.
	++newCharset->numUsedChars;

	partialCharsetCompress(newCharset, cleanedWormCharset, mappingTable);
}

void buffferPrint(FILE *f, Buffer *buffer)
{
	int index = 0;
	fprintf(f, "{");
	for (;;)
	{
		fprintf(f, "\n");
		for (int j = 0; j < 16; ++j)
		{
			fprintf(f, "0x%.2X", buffer->content[index]);
			++index;
			if (index >= buffer->length)
			{
				goto done;
			}
			fprintf(f, ", ");
		}
	}
done:
	fprintf(f, "}");
}

void printPlayerStart(FILE *f, PlayerStart *playerStart)
{
	char directionNameUp[] = "Direction_up";
	char directionNameRight[] = "Direction_right";
	char directionNameDown[] = "Direction_down";
	char directionNameLeft[] = "Direction_left";
	char *directionNames[] = {
		directionNameUp,
		directionNameRight,
		directionNameDown,
		directionNameLeft,
	};

	fprintf(f, "{{%i,%i}, %s},", playerStart->position.x, playerStart->position.y, directionNames[playerStart->direction]);
}

void compressLevel(
	Level *level,
	Buffer *compressedChars,
	Buffer *compressedColors)
{
	{
		Buffer original = bufferCreate(level->chars, 1000, 1000);
		lz77Compress(&original, compressedChars);
	}
	{
		Buffer original = bufferCreate(level->colors, 1000, 1000);
		lz77Compress(&original, compressedColors);
	}
}

void printLevelData(
	FILE *f,
	Level *level,
	Buffer *compressedChars,
	Buffer *compressedColors,
	int levelIndex)
{
	fprintf(f, "\nchar _LEVEL_DATA_NAME_%i[] = \"%s\";\n", levelIndex, level->name);

	fprintf(f, "\nuint8_t _LEVEL_DATA_MULTI_COLOR_1_%i[1] = {%i};\n", levelIndex, level->multiColor1);
	fprintf(f, "\nuint8_t _LEVEL_DATA_MULTI_COLOR_2_%i[1] = {%i};\n", levelIndex, level->multiColor2);

	fprintf(f, "\nPlayerStart _LEVEL_DATA_PLAYER_STARTS_%i[4] = ", levelIndex);
	fprintf(f, "{");
	for (int i = 0; i < 4; ++i)
	{
		printPlayerStart(f, &level->playerStarts[i]);
	}
	fprintf(f, "};\n\n");

	fprintf(f, "\nuint8_t _LEVEL_DATA_CHARS_%i[] = ", levelIndex);
	buffferPrint(f, compressedChars);
	fprintf(f, ";\n\n");

	fprintf(f, "\nuint8_t _LEVEL_DATA_COLORS_%i[] = ", levelIndex);
	buffferPrint(f, compressedColors);
	fprintf(f, ";\n\n");
}

void printLevelsStructArray(FILE *f, int numLevels)
{
	fprintf(f, "Level levels[] = {\n");
	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		fprintf(f, "{");
		{
			fprintf(f, "_LEVEL_DATA_NAME_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_MULTI_COLOR_1_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_MULTI_COLOR_2_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_PLAYER_STARTS_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_CHARS_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_COLORS_%i,", levelIndex);
		}
		fprintf(f, "},\n");
	}
	fprintf(f, "};\n\n");
}

extern Charset originalWormCharset;

int main()
{
	PartialCharset newCharset;
	uint8_t mappingTable[256];

	unmapCharset(&newCharset, mappingTable, originalWormCharset);

	printf("numLevels: %i\n", numLevels);
	for (int i = 0; i < numLevels; ++i)
	{
		printf("level: %i\n", i);
		partialCharsetAddNewCharsUsedInLevel(&newCharset, *(levels[i].charset), levels[i].chars);
	}
	for (int i = 0; i < numLevels; ++i)
	{
		levelRemapChars(&levels[i], newCharset.charset);
	}

	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		levelRemoveInvisibleColorChanges(&levels[levelIndex]);
	}

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

	FILE *levelsFile = fopen("../levels.c", "w");
	if (levelsFile == NULL)
	{
		printf("Error opening levels.c!\n");
		exit(1);
	}

	fprintf(levelsFile, "#include \"levels.h\"\n");

	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		uint8_t compressedCharsContent[2000];
		uint8_t compressedColorsContent[2000];

		Buffer compressedChars = bufferCreate(compressedCharsContent, 0, sizeof(compressedCharsContent));
		Buffer compressedColors = bufferCreate(compressedColorsContent, 0, sizeof(compressedColorsContent));

		compressLevel(&levels[levelIndex], &compressedChars, &compressedColors);
		printLevelData(levelsFile, &levels[levelIndex], &compressedChars, &compressedColors, levelIndex);
	}

	printLevelsStructArray(levelsFile, numLevels);

	fprintf(levelsFile, "int numLevels = sizeof(levels) / sizeof(levels[0]);\n");

	return 0;
}
