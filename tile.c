#include "tile.h"
#include "direction.h"
#include <stdbool.h>
#include <stdint.h>

int8_t bendOffsetsClockwiseFromTopLeft[] = {0, 1, 17, 16};

Tile tileCreate(TileType type, Direction lastDirection, Direction direction, Microstep step)
{
	// Step has extra precision bits.
	step >>= 2;

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
	else
	{

		bool clockwise = ((lastDirection + 1) & 3) == direction;

		if (clockwise)
		{
			uint8_t tileQuadrant = (direction + 3) & 3;
			uint8_t headQuadrant = (tileQuadrant + type) & 3;
			uint8_t quadrantOffset = (4 + headQuadrant - type) & 3;

			uint8_t group = (headQuadrant + 3) & 3;
			uint8_t groupOffsetX = group % 2;
			uint8_t groupOffsetY = group / 2;

			return Tile_worm_clockwise_start + 8 * groupOffsetX + 2 * 16 * groupOffsetY + 2 * ((step + 3) & 3) + bendOffsetsClockwiseFromTopLeft[quadrantOffset];
		}
		else
		{
			uint8_t tileQuadrant = (direction + 2) & 3;
			uint8_t headQuadrant = (tileQuadrant - type + 4) & 3;
			uint8_t quadrantOffset = (4 + headQuadrant + type) & 3;

			uint8_t group = (3 - headQuadrant) & 3;
			uint8_t groupOffsetX = group % 2;
			uint8_t groupOffsetY = group / 2;

			return Tile_worm_anti_clockwise_start + 8 * groupOffsetX + 2 * 16 * groupOffsetY + 2 * ((step + 3) & 3) + bendOffsetsClockwiseFromTopLeft[quadrantOffset];
		}
	}

	return Tile_error;
}
