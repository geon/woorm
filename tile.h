#ifndef TILE_H
#define TILE_H

#include "direction.h"
#include "microstep.h"
#include "tile-to-index.h"
#include "tile-type.h"
#include <stdint.h>

uint8_t tilePackWormTileStateInBits(TileType type, Direction lastDirection, Direction direction, Microstep step);

#endif
