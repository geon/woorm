#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include "microstep.h"
#include "screen.h"
#include "tile-type.h"
#include <stdint.h>

typedef struct Worm
{
	Screen *screen;
	uint8_t color;
	Direction wantedNextDirection;
	Direction nextDirection;
	uint8_t speed;
	Microstep step;

	CircularBuffer tail;
	// The actual values of the CircularBuffer are stored separately, in multiple arrays.
	Direction tailDirections[0x100];
	uint16_t tailPositions[0x100];

} Worm;

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction, uint8_t color);
void wormSetNextDirection(Worm *worm, Direction direction);
void wormSetSpeed(Worm *worm, uint8_t speed);
void wormStep(Worm *worm);

// For benchmark only.
void wormDraw(Worm *worm);
void wormLazyDraw(Worm *worm);

#endif
