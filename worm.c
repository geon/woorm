#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

void wormDraw(Worm *worm, Screen *screen, uint16_t pos, Direction direction);

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction)
{
	wormDraw(worm, screen, pos, direction);
}

void wormDraw(Worm *worm, Screen *screen, uint16_t pos, Direction direction)
{
	int part;

	for (part = TileType_animated_head; part <= TileType_animated_end; ++part)
	{
		screen->chars[pos] = tileCreate(part, direction, direction, Microstep_0);
		screen->colors[pos] = 14;
		pos -= getPositionOffsetForDirection(direction);
	}
}
