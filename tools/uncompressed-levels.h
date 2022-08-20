#ifndef LEVELS_H
#define LEVELS_H

#include "../coord.h"
#include "../direction.h"
#include <stdint.h>

typedef struct PlayerStart
{
	Coord position;
	Direction direction;
} PlayerStart;

typedef uint8_t LevelAttributes[1000];

typedef struct Level
{
	char *name;
	PlayerStart playerStarts[4];
	LevelAttributes chars;
	LevelAttributes colors;
} Level;

extern Level levels[];

#endif