#include "tile.h"
#include "direction.h"
#include "tile.h"
#include <stdbool.h>
#include <stdint.h>

uint8_t tilePackWormTileStateInBits(TileType type, Direction lastDirection, Direction direction, Microstep step)
{
	// Just pack the bits as tightly asap.
	// `step` already has the relevant bits in the right place.
	return (uint8_t)((uint8_t)type << 6) | ((uint8_t)lastDirection << 4) | ((uint8_t)step & 0b1100) | ((uint8_t)direction << 0);
}
