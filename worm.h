#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include "microstep.h"
#include "screen.h"
#include "tile-type.h"
#include <stdint.h>

typedef struct TailCell
{
	Direction direction;
	uint16_t position;
	// Array element size should be 1, 2, 4 or 8 bytes for speed.
	// Also crashes without this.
	uint8_t PADDING;
} TailCell;

typedef struct Worm
{
	Screen *screen;
	uint8_t color;
	Direction wantedNextDirection;
	Direction nextDirection;
	Microstep headStep;
	Microstep tailStep;
	bool hasNextStep;
	TailCell nextStep;

	CircularBuffer tail;
	// The actual values of the CircularBuffer are stored separately, in multiple arrays.
	Direction tailDirections[0x100];
	uint16_t tailPositions[0x100];
} Worm;

void wormInit(uint8_t wormIndex, Screen *screen, uint16_t pos, Direction direction, uint8_t color);
void wormSetNextDirection(uint8_t wormIndex, Direction direction);
void wormStep(uint8_t wormIndex);

// For benchmark only.
void wormDraw(uint8_t wormIndex);
void wormLazyDraw(uint8_t wormIndex);

#endif
