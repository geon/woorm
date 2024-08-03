#include "level.h"
#include "lz77.h"
#include <c64.h>

void levelDraw(Level *level, Screen *screen)
{
	// Decompress directly to screen.
	lz77Decompress(level->chars, 1024, screen->chars, 1024);
	lz77Decompress(level->colors, 1024, screen->colors, 1024);
}

uint8_t wormColors[] = {
	COLOR_CYAN,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_RED,
};

void levelStart(Level *level, Screen *screen, Worm worms[], uint8_t numWorms)
{
	uint8_t index;
	levelSetMultiColors(level);
	levelDraw(level, screen);
	for (index = 0; index < numWorms; ++index)
	{
		wormInit(&worms[index], screen, coordToPos(level->playerStarts[index].position), level->playerStarts[index].direction, wormColors[index] + 8);
	}
}

void levelSetMultiColors(Level *level)
{
	// Registers 0xD022, 0xD023
	VIC.bgcolor1 = *level->multiColor1;
	VIC.bgcolor2 = *level->multiColor2;
}
