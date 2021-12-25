#include "level.h"
#include "screen.h"
#include <c64.h>

void levelDraw(Level *level, Screen *screen)
{
	uint16_t i;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = level->chars[i];
		screen->colors[i] = level->colors[i];
	}
}
