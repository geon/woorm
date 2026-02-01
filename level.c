#include "level.h"
#include "lz77.h"
#include <c64.h>

void levelDraw(Level *level)
{
	// Decompress directly to screen.
	lz77Decompress(level->chars, 1024, screenChars, 1024);
	lz77Decompress(level->colors, 1024, screenColors, 1024);
}

void levelStart(Level *level, uint8_t numWorms)
{
	uint8_t index;
	levelSetMultiColors(level);
	levelDraw(level);
	for (index = 0; index < numWorms; ++index)
	{
		wormInit(index, coordToPos(level->playerStarts[index].position), level->playerStarts[index].direction);
	}
}

void levelSetMultiColors(Level *level)
{
	// Registers 0xD022, 0xD023
	VIC.bgcolor1 = *level->multiColor1;
	VIC.bgcolor2 = *level->multiColor2;
}
