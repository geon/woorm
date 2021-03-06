#include "coord.h"
#include "direction.h"
#include <stdint.h>

#define SCREEN_WIDTH 40
// #define SCREEN_HEIGHT 25

Coord coordCreate(uint8_t x, uint8_t y)
{
	Coord coord;
	coord.x = x;
	coord.y = y;
	return coord;
}

uint16_t coordToPos(Coord coord)
{
	return coord.x + coord.y * SCREEN_WIDTH;
}

Coord posToCoord(uint16_t pos)
{
	Coord coord;
	coord.x = (uint8_t)(pos % SCREEN_WIDTH);
	coord.y = (uint8_t)(pos / SCREEN_WIDTH);
	return coord;
}

// offsets for Direction_up, Direction_right, Direction_down, Direction_left.
int8_t offsets[Direction_count] = {-SCREEN_WIDTH, 1, SCREEN_WIDTH, -1};
int8_t getPositionOffsetForDirection(Direction direction)
{
	return offsets[direction];
}
