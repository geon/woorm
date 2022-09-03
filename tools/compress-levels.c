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

int main()
{
	FILE *f = fopen("../levels.c", "w");
	if (f == NULL)
	{
		printf("Error opening levels.c!\n");
		exit(1);
	}

	int compressedSize = 0;

	fprintf(f, "#include \"levels.h\"\n");
	// int levelIndex = 1;
	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		uint8_t compressedContent[2000];
		Level *level = &levels[levelIndex];

		fprintf(f, "\nchar _LEVEL_DATA_NAME_%i[] = \"%s\";\n", levelIndex, level->name);
		fprintf(f, "\nuint8_t _LEVEL_DATA_CHARS_%i[] = ", levelIndex);

		{
			Buffer original = bufferCreate(level->chars, 1000, 1000);
			Buffer compressed = bufferCreate(compressedContent, 0, sizeof(compressedContent));
			lz77Compress(&original, &compressed);
			buffferPrint(f, &compressed);
			compressedSize += compressed.length;
		}

		fprintf(f, ";\n\n");
		fprintf(f, "\nuint8_t _LEVEL_DATA_COLORS_%i[] = ", levelIndex);

		{
			Buffer original = bufferCreate(level->colors, 1000, 1000);
			Buffer compressed = bufferCreate(compressedContent, 0, sizeof(compressedContent));
			levelRemoveInvisibleColorChanges(level);
			lz77Compress(&original, &compressed);
			buffferPrint(f, &compressed);
			compressedSize += compressed.length;
		}

		fprintf(f, ";\n\n");
	}

	fprintf(f, "Level levels[] = {\n");
	for (int levelIndex = 0; levelIndex < numLevels; ++levelIndex)
	{
		Level *level = &levels[levelIndex];

		fprintf(f, "{");
		{
			fprintf(f, "_LEVEL_DATA_NAME_%i,", levelIndex);
			fprintf(f, "{");
			for (int i = 0; i < 4; ++i)
			{
				printPlayerStart(f, &level->playerStarts[i]);
			}
			fprintf(f, "},");
			fprintf(f, "_LEVEL_DATA_CHARS_%i,", levelIndex);
			fprintf(f, "_LEVEL_DATA_COLORS_%i,", levelIndex);
		}
		fprintf(f, "},");
	}
	fprintf(f, "};\n\n");
}
