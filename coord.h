#ifndef COORD_H
#define COORD_H

#include <stdint.h>
#include "direction.h"

typedef struct Coord
{
    uint8_t x;
    uint8_t y;
} Coord;

Coord coordCreate(uint8_t x, uint8_t y);
uint16_t coordToPos(Coord coord);
Coord posToCoord(uint16_t pos);
int8_t getPositionOffsetForDirection(Direction direction);

#endif
