#include "buffer.h"
#include "lz77.h"
#include "uncompressed-levels.h"
#include <stdio.h>

void buffferPrint(Buffer *buffer)
{
	int index = 0;
	printf("{");
	for (;;)
	{
		printf("\n");
		for (int j = 0; j < 16; ++j)
		{
			printf("0x%.2X", buffer->content[index]);
			++index;
			if (index >= buffer->length)
			{
				goto done;
			}
			printf(", ");
		}
	}
done:
	printf("}");
}

void printPlayerStart(PlayerStart *playerStart)
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

	printf("{{%i,%i}, %s},", playerStart->position.x, playerStart->position.y, directionNames[playerStart->direction]);
}

int main()
{
	int compressedSize = 0;

	printf("#include \"levels.h\"\n");
	// int levelIndex = 1;
	for (int levelIndex = 0; levelIndex < 21; ++levelIndex)
	{
		uint8_t compressedContent[2000];
		Level *level = &levels[levelIndex];

		printf("\nchar _LEVEL_DATA_NAME_%i[] = \"%s\";\n", levelIndex, level->name);
		printf("\nuint8_t _LEVEL_DATA_CHARS_%i[] = ", levelIndex);

		{
			Buffer original = bufferCreate(level->chars, 1000, 1000);
			Buffer compressed = bufferCreate(compressedContent, 0, sizeof(compressedContent));
			lz77Compress(&original, &compressed);
			buffferPrint(&compressed);
			compressedSize += compressed.length;
		}

		printf(";\n\n");
		printf("\nuint8_t _LEVEL_DATA_COLORS_%i[] = ", levelIndex);

		{
			Buffer original = bufferCreate(level->colors, 1000, 1000);
			Buffer compressed = bufferCreate(compressedContent, 0, sizeof(compressedContent));
			// levelRemoveInvisibleColorChanges(level);
			lz77Compress(&original, &compressed);
			buffferPrint(&compressed);
			compressedSize += compressed.length;
		}

		printf(";\n\n");
	}

	printf("Level levels[] = {\n");
	for (int levelIndex = 0; levelIndex < 21; ++levelIndex)
	{
		Level *level = &levels[levelIndex];

		printf("{");
		{
			printf("_LEVEL_DATA_NAME_%i,", levelIndex);
			printf("{");
			for (int i = 0; i < 4; ++i)
			{
				printPlayerStart(&level->playerStarts[i]);
			}
			printf("},");
			printf("_LEVEL_DATA_CHARS_%i,", levelIndex);
			printf("_LEVEL_DATA_COLORS_%i,", levelIndex);
		}
		printf("},");
	}
	printf("};\n\n");
}
