#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <stdint.h>

typedef uint8_t TileType;

#define TileType_first 0

#define TileType_animated_head TileType_first
#define TileType_animated_headToMiddle 1
#define TileType_animated_endToMiddle 2
#define TileType_animated_end 3

#define TileType_middle 4

// Not same as Tile_empty, which must be zero.
#define TileType_empty 5

#define TileType_count 6

#endif
