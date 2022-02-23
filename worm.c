#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

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
	circularBufferGetValue(worm->tailValues, index).direction = direction;
	circularBufferGetValue(worm->tailValues, index).position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailValues, index).direction = direction;
	circularBufferGetValue(worm->tailValues, index).position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailValues, index).direction = direction;
	circularBufferGetValue(worm->tailValues, index).position = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailValues, index).direction = direction;
	circularBufferGetValue(worm->tailValues, index).position = position;

	wormDraw(worm);
}

void wormSetNextDirection(Worm *worm, Direction direction)
{
	worm->wantedNextDirection = direction;
}

void wormStep(Worm *worm)
{
	if (!worm->step)
	{
		uint8_t index;
		TailCell currentHeadCell;
		Direction direction;
		uint16_t nextPos;

		currentHeadCell = circularBufferGetLastValue(worm->tail, worm->tailValues);

		// Try stepping in the selected direction.
		direction = worm->wantedNextDirection;
		nextPos = currentHeadCell.position + getPositionOffsetForDirection(direction);

		// If the selected direction is blocked, first try the previous direction.
		if (worm->screen->chars[nextPos])
		{
			direction = circularBufferGetLastValue(worm->tail, worm->tailValues).direction;
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
		circularBufferGetValue(worm->tailValues, index).direction = direction;
		circularBufferGetValue(worm->tailValues, index).position = nextPos;
		circularBufferPop(&worm->tail, &index);
	}

	worm->step = (worm->step + 1) & 3;
	wormLazyDraw(worm);
}

TileType wormGetPart(Worm *worm, uint8_t iterator);

TileType wormGetPart(Worm *worm, uint8_t iterator)
{
	CircularBuffer *tail = &worm->tail;

	TileType part;
	if (iterator == tail->end - 1)
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

	return part;
}

void wormDraw(Worm *worm)
{
	Direction nextDirection = worm->nextDirection;
	CircularBuffer *tail = &worm->tail;
	TileType part;
	uint8_t iterator;
	Screen *screen = worm->screen;
	TileType foo;
	TailCell cell;
	circularBufferForEachReverse(tail, iterator)
	{
		cell = circularBufferGetValue(worm->tailValues, iterator);
		part = wormGetPart(worm, iterator);

		screen->chars[cell.position] = tileCreate(part, cell.direction, nextDirection, worm->step);
		screen->colors[cell.position] = worm->color;

		nextDirection = cell.direction;
	}
}

void wormLazyDraw(Worm *worm)
{
	Direction nextDirection = worm->nextDirection;
	CircularBuffer *tail = &worm->tail;

	Screen *screen = worm->screen;
	TileType foo;
	TailCell cell;

	cell = circularBufferGetValue(worm->tailValues, tail->end - 1);
	screen->chars[cell.position] = tileCreate(TileType_animated_head, cell.direction, nextDirection, worm->step);
	screen->colors[cell.position] = worm->color;
	nextDirection = cell.direction;

	cell = circularBufferGetValue(worm->tailValues, tail->end - 2);
	screen->chars[cell.position] = tileCreate(TileType_animated_headToMiddle, cell.direction, nextDirection, worm->step);
	nextDirection = circularBufferGetValue(worm->tailValues, worm->tail.begin + 2).direction;

	cell = circularBufferGetValue(worm->tailValues, tail->begin + 1);
	screen->chars[cell.position] = tileCreate(TileType_animated_endToMiddle, cell.direction, nextDirection, worm->step);
	nextDirection = cell.direction;

	cell = circularBufferGetValue(worm->tailValues, tail->begin);
	screen->chars[cell.position] = tileCreate(TileType_animated_end, cell.direction, nextDirection, worm->step);
	nextDirection = cell.direction;
}
