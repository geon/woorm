#ifndef LEVEL_H
#define LEVEL_H

#include "coord.h"
#include "direction.h"
#include "screen.h"
#include <stdint.h>

typedef struct PlayerStart
{
	Coord position;
	Direction direction;
} PlayerStart;

typedef uint8_t LevelAttributes[1000];

typedef struct Level
{
	PlayerStart playerStarts[4];
	LevelAttributes chars;
	LevelAttributes colors;
} Level;

void levelDraw(Level *level, Screen *screen);

#endif
