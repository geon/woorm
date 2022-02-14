#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

void wormDraw(Worm *worm);

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction, uint8_t color)
{
	uint8_t index;
	uint16_t position = pos - getPositionOffsetForDirection(direction) * 3;

	worm->wantedNextDirection = direction;
	worm->nextDirection = direction;
	worm->step = Microstep_0;
	worm->color = color;
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

void wormSetNextDirection(Worm *worm, Direction direction)
{
	worm->wantedNextDirection = direction;
}

void wormStep(Worm *worm)
{
	uint8_t index;
	TailCell currentHeadCell;

	currentHeadCell = worm->tailValues[worm->tail.end - 1];

	if (!worm->step)
	{
		// Try stepping in the selected direction.
		Direction direction = worm->wantedNextDirection;
		uint16_t nextPos = currentHeadCell.position + getPositionOffsetForDirection(direction);

		// If the selected direction is blocked, first try the previous direction.
		if (worm->screen->chars[nextPos])
		{
			direction = worm->tailValues[worm->tail.end - 1].direction;
			nextPos = currentHeadCell.position + getPositionOffsetForDirection(direction);
		}
		// If the direction is blocked, turn clockwise.
		if (worm->screen->chars[nextPos])
		{
			direction = (direction + 1) & 3;
			nextPos = currentHeadCell.position + getPositionOffsetForDirection(direction);
		}
		// If still blocked, try anti-clockwise instead.
		if (worm->screen->chars[nextPos])
		{
			direction = (direction + 2) & 3;
			nextPos = currentHeadCell.position + getPositionOffsetForDirection(direction);
		}

		worm->nextDirection = direction;

		// If still blocked, just don't move.
		if (worm->screen->chars[nextPos])
		{
			return;
		}

		circularBufferPush(&worm->tail, &index);
		worm->tailValues[index].direction = direction;
		worm->tailValues[index].position = nextPos;
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
	Direction nextDirection = worm->nextDirection;

	circularBufferForEachReverse(tail, iterator)
	{
		uint8_t part;
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

		screen->chars[cell.position] = tileCreate(part, cell.direction, nextDirection, worm->step);
		screen->colors[cell.position] = worm->color;

		nextDirection = cell.direction;
	}
}
