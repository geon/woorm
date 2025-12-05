#ifndef LEVEL_H
#define LEVEL_H

#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "worm.h"
#include <stdint.h>

typedef struct PlayerStart
{
	Coord position;
	Direction direction;
} PlayerStart;

typedef struct Level
{
	char *name;
	uint8_t *multiColor1;
	uint8_t *multiColor2;
	PlayerStart *playerStarts;
	uint8_t *chars;
	uint8_t *colors;
} Level;

void levelDraw(Level *level, Screen *screen);
void levelStart(Level *level, Screen *screen, uint8_t numWorms);
void levelSetMultiColors(Level *level);

#endif
