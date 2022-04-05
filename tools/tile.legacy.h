#ifndef TILE_LEGACY_H
#define TILE_LEGACY_H

#include "../tile.h"

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

	// The part order is backwards to look better in the charset.
	// Tile_name_direction_part_step
	Tile_worm_right_start = Tile_first + 16 * 1 + 4,
	Tile_worm_right_3_1 = Tile_worm_right_start + 16 * 0,
	Tile_worm_right_2_1,
	Tile_worm_right_1_1,
	Tile_worm_right_0_1,
	Tile_worm_right_3_2 = Tile_worm_right_start + 16 * 1,
	Tile_worm_right_2_2,
	Tile_worm_right_1_2,
	Tile_worm_right_0_2,
	Tile_worm_right_3_3 = Tile_worm_right_start + 16 * 2,
	Tile_worm_right_2_3,
	Tile_worm_right_1_3,
	Tile_worm_right_0_3,
	Tile_worm_right_3_0 = Tile_worm_right_start + 16 * 3,
	Tile_worm_right_2_0,
	Tile_worm_right_1_0,
	Tile_worm_right_0_0,

	// The part order is backwards to look better in the charset.
	// Tile_name_direction_step_part
	Tile_worm_down_start = Tile_first + 16 * 1 + 8,
	Tile_worm_down_1_3 = Tile_worm_down_start + 16 * 0,
	Tile_worm_down_2_3,
	Tile_worm_down_3_3,
	Tile_worm_down_0_3,
	Tile_worm_down_1_2 = Tile_worm_down_start + 16 * 1,
	Tile_worm_down_2_2,
	Tile_worm_down_3_2,
	Tile_worm_down_0_2,
	Tile_worm_down_1_1 = Tile_worm_down_start + 16 * 2,
	Tile_worm_down_2_1,
	Tile_worm_down_3_1,
	Tile_worm_down_0_1,
	Tile_worm_down_1_0 = Tile_worm_down_start + 16 * 3,
	Tile_worm_down_2_0,
	Tile_worm_down_3_0,
	Tile_worm_down_0_0,

	// Tile_name_direction_part_step
	Tile_worm_left_start = Tile_first + 16 * 1 + 12,
	Tile_worm_left_0_1 = Tile_worm_left_start + 16 * 0,
	Tile_worm_left_1_1,
	Tile_worm_left_2_1,
	Tile_worm_left_3_1,
	Tile_worm_left_0_2 = Tile_worm_left_start + 16 * 1,
	Tile_worm_left_1_2,
	Tile_worm_left_2_2,
	Tile_worm_left_3_2,
	Tile_worm_left_0_3 = Tile_worm_left_start + 16 * 2,
	Tile_worm_left_1_3,
	Tile_worm_left_2_3,
	Tile_worm_left_3_3,
	Tile_worm_left_0_0 = Tile_worm_left_start + 16 * 3,
	Tile_worm_left_1_0,
	Tile_worm_left_2_0,
	Tile_worm_left_3_0,

	Tile_worm_clockwise_start = Tile_first + 16 * 5 + 0,
	// Tile_name_direction_part_step
	Tile_worm_right_down_0_1 = Tile_worm_clockwise_start + 1 + 16 * 0 + 2 * 0,
	Tile_worm_right_down_0_2 = Tile_worm_clockwise_start + 1 + 16 * 0 + 2 * 1,
	Tile_worm_right_down_0_3 = Tile_worm_clockwise_start + 1 + 16 * 0 + 2 * 2,
	Tile_worm_right_down_0_0 = Tile_worm_clockwise_start + 1 + 16 * 0 + 2 * 3,

	Tile_worm_up_right_1_1 = Tile_worm_clockwise_start + 0 + 16 * 0 + 2 * 0,
	Tile_worm_up_right_1_2 = Tile_worm_clockwise_start + 0 + 16 * 0 + 2 * 1,
	Tile_worm_up_right_1_3 = Tile_worm_clockwise_start + 0 + 16 * 0 + 2 * 2,
	Tile_worm_up_right_1_0 = Tile_worm_clockwise_start + 0 + 16 * 0 + 2 * 3,

	Tile_worm_left_up_2_1 = Tile_worm_clockwise_start + 0 + 16 * 1 + 2 * 0,
	Tile_worm_left_up_2_2 = Tile_worm_clockwise_start + 0 + 16 * 1 + 2 * 1,
	Tile_worm_left_up_2_3 = Tile_worm_clockwise_start + 0 + 16 * 1 + 2 * 2,
	Tile_worm_left_up_2_0 = Tile_worm_clockwise_start + 0 + 16 * 1 + 2 * 3,

	Tile_worm_down_left_3_1 = Tile_worm_clockwise_start + 1 + 16 * 1 + 2 * 0,
	Tile_worm_down_left_3_2 = Tile_worm_clockwise_start + 1 + 16 * 1 + 2 * 1,
	Tile_worm_down_left_3_3 = Tile_worm_clockwise_start + 1 + 16 * 1 + 2 * 2,
	Tile_worm_down_left_3_0 = Tile_worm_clockwise_start + 1 + 16 * 1 + 2 * 3,

	// ^ There are more clockwise groups, but I can't be arsed to add tests for them, so I don't need enums either.

	Tile_worm_anti_clockwise_start = Tile_first + 16 * 9 + 0,
	// Tile_name_direction_part_step
	Tile_worm_down_right_0_1 = Tile_worm_anti_clockwise_start + 0 + 16 * 1 + 2 * 0,
	Tile_worm_down_right_0_2 = Tile_worm_anti_clockwise_start + 0 + 16 * 1 + 2 * 1,
	Tile_worm_down_right_0_3 = Tile_worm_anti_clockwise_start + 0 + 16 * 1 + 2 * 2,
	Tile_worm_down_right_0_0 = Tile_worm_anti_clockwise_start + 0 + 16 * 1 + 2 * 3,

	Tile_worm_left_down_1_1 = Tile_worm_anti_clockwise_start + 0 + 16 * 0 + 2 * 0,
	Tile_worm_left_down_1_2 = Tile_worm_anti_clockwise_start + 0 + 16 * 0 + 2 * 1,
	Tile_worm_left_down_1_3 = Tile_worm_anti_clockwise_start + 0 + 16 * 0 + 2 * 2,
	Tile_worm_left_down_1_0 = Tile_worm_anti_clockwise_start + 0 + 16 * 0 + 2 * 3,

	Tile_worm_up_left_2_1 = Tile_worm_anti_clockwise_start + 1 + 16 * 0 + 2 * 0,
	Tile_worm_up_left_2_2 = Tile_worm_anti_clockwise_start + 1 + 16 * 0 + 2 * 1,
	Tile_worm_up_left_2_3 = Tile_worm_anti_clockwise_start + 1 + 16 * 0 + 2 * 2,
	Tile_worm_up_left_2_0 = Tile_worm_anti_clockwise_start + 1 + 16 * 0 + 2 * 3,

	Tile_worm_right_up_3_1 = Tile_worm_anti_clockwise_start + 1 + 16 * 1 + 2 * 0,
	Tile_worm_right_up_3_2 = Tile_worm_anti_clockwise_start + 1 + 16 * 1 + 2 * 1,
	Tile_worm_right_up_3_3 = Tile_worm_anti_clockwise_start + 1 + 16 * 1 + 2 * 2,
	Tile_worm_right_up_3_0 = Tile_worm_anti_clockwise_start + 1 + 16 * 1 + 2 * 3,

	// Used for level drawing until the real graphics is in place.
	Tile_filled = 255,

	Tile_count,
	Tile_error
} Tile;

Tile tileCreate(TileType type, Direction lastDirection, Direction direction, Microstep step);

#endif
