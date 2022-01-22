#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include "direction.h"

typedef enum TileType
{
	TileType_first,

	TileType_animated_head = TileType_first,
	TileType_animated_headToMiddle,
	TileType_animated_endToMiddle,
	TileType_animated_end,

	TileType_middle,

	// Not same as Tile_empty, which must be zero.
	TileType_empty,

	TileType_count
} TileType;

#endif
