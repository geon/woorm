#include "level.h"
#include "lz77.h"
#include <c64.h>

void levelDraw(Level *level, Screen *screen)
{
	// Decompress directly to screen.
	lz77Decompress(level->chars, 1024, screen->chars, 1024);
	lz77Decompress(level->colors, 1024, screen->colors, 1024);
}

void levelStart(Level *level, Screen *screen, Worm worms[4])
{
	levelDraw(level, screen);
	wormInit(&worms[0], screen, coordToPos(level->playerStarts[0].position), level->playerStarts[0].direction, COLOR_CYAN + 8);
	wormInit(&worms[1], screen, coordToPos(level->playerStarts[1].position), level->playerStarts[1].direction, COLOR_GREEN + 8);
	wormInit(&worms[2], screen, coordToPos(level->playerStarts[2].position), level->playerStarts[2].direction, COLOR_YELLOW + 8);
	wormInit(&worms[3], screen, coordToPos(level->playerStarts[3].position), level->playerStarts[3].direction, COLOR_RED + 8);
}
