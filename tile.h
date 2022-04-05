#ifndef TILE_H
#define TILE_H

#include "direction.h"
#include "microstep.h"
#include "tile-type.h"
#include <stdint.h>

uint8_t tilePackWormTileStateInBits(TileType type, Direction lastDirection, Direction direction, Microstep step);

extern uint8_t tileToIndex[256];

#endif
