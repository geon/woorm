#include "level.h"
#include "levels.h"
#include "screen-location-c64.h"
#include "worm.h"
#include "worms.h"
#include <joystick.h>
#include <stdint.h>

void animateWormTitleScreen(uint8_t wormIndex, uint8_t path[], uint8_t *currentPathStep, uint8_t pathStepCount)
{
	Worm *worm = &worms[wormIndex];

	wormStep(wormIndex);
	if (worm->headStep == 0)
	{
		worm->wantedNextDirection = path[*currentPathStep];

		++(*currentPathStep);
		if (*currentPathStep >= pathStepCount)
		{
			*currentPathStep = 0;
		}
	}
}

uint8_t pathA[] = {
	Direction_right,
	Direction_right,
	Direction_down,
	Direction_down,
	Direction_left,
	Direction_left,
	Direction_up,
	Direction_up,
};
uint8_t pathB[] = {
	Direction_right,
	Direction_right,
	Direction_down,
	Direction_down,
	Direction_down,
	Direction_left,
	Direction_left,
	Direction_up,
	Direction_up,
	Direction_up,
};

void titleScreen(void)
{
	uint8_t pathStepA = 0;
	uint8_t pathStepB = 0;

	levelStart(&levels[(numLevels - 1)], screen, 2);
	// worms[0].wantedLength = sizeof(pathA) - 2;
	// worms[1].wantedLength = sizeof(pathB) - 2;

	for (;;)
	{
		if (JOY_FIRE(joy_read(JOY_1)) || JOY_FIRE(joy_read(JOY_2)))
		{
			break;
		}

		waitvsync();
		animateWormTitleScreen(0, pathA, &pathStepA, sizeof(pathA));
		animateWormTitleScreen(1, pathB, &pathStepB, sizeof(pathB));
	}
}
