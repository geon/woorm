#include "coord.h"
#include "direction.h"
#include "level.h"
#include "levels.h"
#include "screen-location-c64.h"
#include "screen.h"
#include "tile.h"
#include "title-screen.h"
#include "worm.h"
#include "worms.h"
#include <c64.h>
#include <conio.h>
#include <joystick.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern Level levels[];

void animateWorm(uint8_t wormIndex, Direction nextDirection)
{
	Worm *worm = &worms[wormIndex];

	wormStep(wormIndex);
	if (nextDirection != Direction_count)
	{
		wormSetNextDirection(wormIndex, nextDirection);
	}
}

void setUpWormCharset()
{
	// Switch to charset at 0x2000. (Charset with index 4 in the default bank, which is the first one not shadowed by rom.)
	// Register 0xD018
	VIC.addr = (VIC.addr & 0xF0) | (4 << 1);

	// Switch to multi color mode.
	// Register 0xD016
	VIC.ctrl2 = VIC.ctrl2 | 16;

	// Not setting the bg colors makes the charset glitch on some levels, unless there is a wait before the level start.
	// Registers 0xD022, 0xD023
	VIC.bgcolor1 = 1;
	VIC.bgcolor2 = 9;
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

void setupJoysticks()
{
	if (JOY_ERR_OK != joy_install(c64_ptvjoy_joy))
	{
		exit(1);
	}
}

Direction joyStateToDirection(uint8_t joyState)
{
	if (JOY_UP(joyState))
	{
		return Direction_up;
	}
	if (JOY_DOWN(joyState))
	{
		return Direction_down;
	}
	if (JOY_LEFT(joyState))
	{
		return Direction_left;
	}
	if (JOY_RIGHT(joyState))
	{
		return Direction_right;
	}

	return Direction_count;
}

Direction getPlayerInput(uint8_t playerIndex)
{
	switch (playerIndex)
	{
		case 0:
			return joyStateToDirection(joy_read(JOY_1));
		case 1:
			return joyStateToDirection(joy_read(JOY_2));

		default:
			return Direction_count;
	}
}

void setup(void)
{
	setupJoysticks();

	srand(time(NULL));

	screenClear(screen);
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);
	setUpWormCharset();
}

void gameLoop(void)
{
	uint8_t levelIndex = 0;
	for (;;)
	{
		levelStart(&levels[levelIndex % (numLevels - 1)], screen, sizeof(worms) / sizeof(Worm));

		for (;;)
		{
			if (JOY_FIRE(joy_read(JOY_1)) || JOY_FIRE(joy_read(JOY_2)))
			{
				break;
			}

			waitvsync();

			bordercolor(wormColors[0]);
			animateWorm(0, getPlayerInput(0));
			bordercolor(wormColors[1]);
			animateWorm(1, getPlayerInput(1));
			bordercolor(wormColors[2]);
			animateWorm(2, getPlayerInput(2));
			bordercolor(wormColors[3]);
			animateWorm(3, getPlayerInput(3));
			bordercolor(COLOR_BLACK);
		}
		++levelIndex;
	}
}

int main(void)
{
	setup();
	titleScreen();
	gameLoop();

	return 0;
}
