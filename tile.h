#ifndef TILE_H
#define TILE_H

#include "direction.h"
#include "microstep.h"
#include "tile-type.h"

typedef enum Tile
{
	Tile_first,

	Tile_empty = Tile_first,

	// Steps are ordered 1-2-3-0 in the charset to make them look better.

	// Tile_name_direction_part_step
	Tile_worm_up_start = Tile_first + 16 * 1,
	Tile_worm_up_0_1 = Tile_worm_up_start + 16 * 0,
	Tile_worm_up_0_2,
	Tile_worm_up_0_3,
	Tile_worm_up_0_0,
	Tile_worm_up_1_1 = Tile_worm_up_start + 16 * 1,
	Tile_worm_up_1_2,
	Tile_worm_up_1_3,
	Tile_worm_up_1_0,
	Tile_worm_up_2_1 = Tile_worm_up_start + 16 * 2,
	Tile_worm_up_2_2,
	Tile_worm_up_2_3,
	Tile_worm_up_2_0,
	Tile_worm_up_3_1 = Tile_worm_up_start + 16 * 3,
	Tile_worm_up_3_2,
	Tile_worm_up_3_3,
	Tile_worm_up_3_0,

	Tile_count,
	Tile_error
} Tile;

Tile tileCreate(TileType type, Direction lastDirection, Direction direction, Microstep step);

#endif
