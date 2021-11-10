#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

void wormDraw(Worm *worm);

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction)
{
	uint8_t index;
	uint16_t position = pos - getPositionOffsetForDirection(direction) * 3;

	worm->nextDirection = direction;
	worm->step = Microstep_0;
	worm->screen = screen;
	circularBufferInit(&worm->tail);

	circularBufferPush(&worm->tail, &index);
	worm->tailValues[index].direction = direction;
	worm->tailValues[index].position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	worm->tailValues[index].direction = direction;
	worm->tailValues[index].position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	worm->tailValues[index].direction = direction;
	worm->tailValues[index].position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	worm->tailValues[index].direction = direction;
	worm->tailValues[index].position = position;

	wormDraw(worm);
}

void wormStep(Worm *worm)
{
	uint8_t index;
	TailCell currentHeadCell;

	currentHeadCell = worm->tailValues[worm->tail.end - 1];

	if (!worm->step)
	{
		circularBufferPush(&worm->tail, &index);
		worm->tailValues[index].direction = worm->nextDirection;
		worm->tailValues[index].position = currentHeadCell.position + getPositionOffsetForDirection(worm->nextDirection);
		circularBufferPop(&worm->tail, &index);
	}

	worm->step = (worm->step + 1) & 3;

	wormDraw(worm);
}

void wormDraw(Worm *worm)
{
	uint8_t iterator;
	CircularBuffer *tail = &worm->tail;
	Screen *screen = worm->screen;
	Direction lastDirection = worm->tailValues[worm->tail.end - 1].direction;

	circularBufferForEachReverse(tail, iterator)
	{
		uint8_t part;
		Tile tile;
		TailCell cell;
		cell = worm->tailValues[iterator];

		if (iterator == worm->tail.end - 1)
		{
			part = TileType_animated_head;
		}
		else if (iterator == tail->end - 2)
		{
			part = TileType_animated_headToMiddle;
		}
		else if (iterator == tail->begin + 1)
		{
			part = TileType_animated_endToMiddle;
		}
		else if (iterator == tail->begin)
		{
			part = TileType_animated_end;
		}
		else
		{
			part = TileType_middle;
		}

		screen->chars[cell.position] = tileCreate(part, lastDirection, cell.direction, worm->step);
		screen->colors[cell.position] = 14;
	}
}
