#include "level.h"
#include <c64.h>

void levelDraw(Level *level, Screen *screen)
{
	uint16_t i = 0;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = level->chars[i];
		screen->colors[i] = level->colors[i];
	}
}

void levelStart(Level *level, Screen *screen, Worm worms[4])
{
	levelDraw(level, screen);
	wormInit(&worms[0], screen, coordToPos(level->playerStarts[0].position), level->playerStarts[0].direction, COLOR_CYAN + 8);
	wormInit(&worms[1], screen, coordToPos(level->playerStarts[1].position), level->playerStarts[1].direction, COLOR_GREEN + 8);
	wormInit(&worms[2], screen, coordToPos(level->playerStarts[2].position), level->playerStarts[2].direction, COLOR_YELLOW + 8);
	wormInit(&worms[3], screen, coordToPos(level->playerStarts[3].position), level->playerStarts[3].direction, COLOR_RED + 8);
}
