#include "tile.h"
#include "direction.h"

Tile tileCreate(TileType type, Direction lastDirection, Direction direction, Microstep step)
{
	// Cover up the tracks.
	if (type == TileType_animated_end && !step)
	{
		return Tile_empty;
	}

	if (direction == lastDirection)
	{
		// Straight

		if (direction == Direction_up)
		{
			return Tile_worm_up_start + (type * 16) + ((3 + step) & 3);
		}

		if (direction == Direction_right)
		{
			return Tile_worm_right_start + (3 - type) + ((3 + step) & 3) * 16;
		}

		if (direction == Direction_down)
		{
			return Tile_worm_down_start + ((3 - type) * 16) + ((3 + step) & 3);
		}

		if (direction == Direction_left)
		{
			return Tile_worm_left_start + (type) + ((3 + step) & 3) * 16;
		}
	}

	return Tile_error;
}
