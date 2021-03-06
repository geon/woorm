#include "coord.h"
#include "direction.h"
#include "level.h"
#include "levels.h"
#include "screen.h"
#include "tile.h"
#include "worm.h"
#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

Worm worms[4];

Screen _screen = {
	(uint8_t *)0x0400,
	(uint8_t *)0xD800};
Screen *screen = &_screen;

extern Level levels[];

void animateWorm(Worm *worm)
{
	wormStep(worm);
	if (worm->step == 0)
	{
		int random = rand() % 8;
		wormSetNextDirection(worm, (worm->nextDirection + (random == 0 ? 1 : (random == 1 ? -1 : 0))) & 3);
	}
}

void setUpWormCharset()
{
	// Switch to charset at 0x2000. (Charset with index 4 in the default bank, which is the first one not shadowed by rom.)
	// 0xD018
	VIC.addr = (VIC.addr & 0xF0) | (4 << 1);

	// Switch to multi color mode.
	// 0xD016
	VIC.ctrl2 = VIC.ctrl2 | 16;

	// Set up secondary char colors.
	// 0xD022
	VIC.bgcolor1 = COLOR_WHITE;
	// 0xD023
	VIC.bgcolor2 = COLOR_BROWN;
}

void waitMs(uint16_t time)
{
	uint16_t frames = time / 20;
	uint8_t i;
	for (i = 0; i < frames; ++i)
	{
		waitvsync();
	}
}

int main(void)
{
	int levelIndex = 6;
	srand(time(NULL));

	screenClear(screen);
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);
	setUpWormCharset();

	levelDraw(&levels[levelIndex], screen);

	waitMs(1000);

	levelStart(&levels[levelIndex], screen, worms);

	wormSetSpeed(&worms[0], 1);
	wormSetSpeed(&worms[1], 2);
	wormSetSpeed(&worms[2], 3);
	wormSetSpeed(&worms[3], 4);

	waitMs(20000);

	for (;;)
	{
		waitvsync();
		animateWorm(&worms[0]);
		animateWorm(&worms[1]);
		animateWorm(&worms[2]);
		animateWorm(&worms[3]);
	}

	return 0;
}
