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
	}

	return Tile_error;
}
