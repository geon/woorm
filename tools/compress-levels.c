#include "buffer.h"
#include "lz77.h"
#include "uncompressed-levels.h"
#include <stdio.h>

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
		levelRemoveInvisibleColorChanges(level);
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

	fprintf(f, "\nPlayerStart _LEVEL_DATA_PLAYER_STARTS_%i[4] = ", levelIndex, level->name);
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
			fprintf(f, "_LEVEL_DATA_PLAYER_STARTS_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_CHARS_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_COLORS_%i,", levelIndex);
		}
		fprintf(f, "},");
	}
	fprintf(f, "};\n\n");
}

void compressLevels(FILE *f, Level *levels, int numLevels)
{
	fprintf(f, "#include \"levels.h\"\n");

	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		uint8_t compressedCharsContent[2000];
		uint8_t compressedColorsContent[2000];

		Buffer compressedChars = bufferCreate(compressedCharsContent, 0, sizeof(compressedCharsContent));
		Buffer compressedColors = bufferCreate(compressedColorsContent, 0, sizeof(compressedColorsContent));

		compressLevel(&levels[levelIndex], &compressedChars, &compressedColors);
		printLevelData(f, &levels[levelIndex], &compressedChars, &compressedColors, levelIndex);
	}

	printLevelsStructArray(f, numLevels);
}

int main()
{
	FILE *f = fopen("../levels.c", "w");
	if (f == NULL)
	{
		printf("Error opening levels.c!\n");
		exit(1);
	}

	compressLevels(f, levels, numLevels);
}
