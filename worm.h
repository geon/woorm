#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include "microstep.h"
#include "screen.h"
#include <stdint.h>

typedef struct TailCell
{
	Direction direction;
	uint16_t position;
} TailCell;

typedef struct Worm
{
	Screen *screen;
	uint8_t color;
	Direction wantedNextDirection;
	Direction nextDirection;
	Microstep step;
	CircularBuffer tail;
	TailCell tailValues[0x100];
} Worm;

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction, uint8_t color);
void wormSetNextDirection(Worm *worm, Direction direction);
void wormStep(Worm *worm);

#endif
