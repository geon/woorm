#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction, uint8_t color)
{
	uint8_t index = 0;
	uint16_t position = pos - getPositionOffsetForDirection(direction) * 3;

	worm->wantedNextDirection = direction;
	worm->nextDirection = direction;
	worm->headStep = Microstep_0;
	worm->color = color;
	worm->screen = screen;
	circularBufferInit(&worm->tail);
	worm->hasNextStep = false;

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

void wormSetNextStep(Worm *worm)
{
	TailCell currentHeadCell = {0, 0};

	currentHeadCell = circularBufferGetLastValue(worm->tail, worm->tailValues);

	// Try stepping in the selected direction.
	worm->nextStep.direction = worm->wantedNextDirection;
	worm->nextStep.position = currentHeadCell.position + getPositionOffsetForDirection(worm->nextStep.direction);
	worm->hasNextStep = true;

	// If the selected direction is blocked, first try the previous direction.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = circularBufferGetLastValue(worm->tail, worm->tailValues).direction;
		worm->nextStep.position = currentHeadCell.position + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If the direction is blocked, turn clockwise.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = (worm->nextStep.direction + 1) & 0b11;
		worm->nextStep.position = currentHeadCell.position + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If still blocked, try anti-clockwise instead.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = (worm->nextStep.direction + 2) & 0b11;
		worm->nextStep.position = currentHeadCell.position + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If still blocked, just don't move.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->hasNextStep = false;
	}
}

void wormFullStep(Worm *worm)
{
	uint8_t index = 0;

	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailValues, index).direction = worm->nextStep.direction;
	circularBufferGetValue(worm->tailValues, index).position = worm->nextStep.position;
	circularBufferPop(&worm->tail, &index);
}

void wormStep(Worm *worm)
{
	uint8_t newStep;

	wormSetNextStep(worm);

	newStep = (worm->headStep + 4) & 0b1111;

	if (newStep == 4)
	{
		if (!worm->hasNextStep)
		{
			// Blocked.
			return;
		}

		wormFullStep(worm);
	}

	worm->nextDirection = worm->nextStep.direction;

	// When forced to turn, forget whatever input the user did, and continue straight forward.
	worm->wantedNextDirection = worm->nextDirection;

	worm->headStep = newStep;

	wormLazyDraw(worm);
}

TileType wormGetPart(Worm *worm, uint8_t iterator);

TileType wormGetPart(Worm *worm, uint8_t iterator)
{
	CircularBuffer *tail = &worm->tail;

	TileType part = 0;
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
	CircularBuffer *tail = &worm->tail;
	TileType part = 0;
	TailCell cell;
	uint8_t iterator;
	Screen *screen = worm->screen;
	Direction nextDirection = worm->nextDirection;

	circularBufferForEachReverse(tail, iterator)
	{

		cell = circularBufferGetValue(worm->tailValues, iterator);
		part = wormGetPart(worm, iterator);

		screen->chars[cell.position] = tileToIndex[tilePackWormTileStateInBits(part, cell.direction, nextDirection, worm->headStep)];
		screen->colors[cell.position] = worm->color;

		nextDirection = cell.direction;
	}
}

void wormLazyDraw(Worm *worm)
{
	Direction nextDirection;
	CircularBuffer *tail = &worm->tail;

	Screen *screen = worm->screen;
	TailCell cell = {0, 0};

	nextDirection = worm->nextDirection;
	cell = circularBufferGetValue(worm->tailValues, tail->end - 1);
	screen->chars[cell.position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, cell.direction, nextDirection, worm->headStep)];

	// Only the cell just entered needs to have the color changed.
	screen->colors[cell.position] = worm->color;

	nextDirection = cell.direction;
	cell = circularBufferGetValue(worm->tailValues, tail->end - 2);
	screen->chars[cell.position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, cell.direction, nextDirection, worm->headStep)];

	nextDirection = circularBufferGetValue(worm->tailValues, worm->tail.begin + 2).direction;
	cell = circularBufferGetValue(worm->tailValues, tail->begin + 1);
	screen->chars[cell.position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, cell.direction, nextDirection, worm->headStep)];

	nextDirection = cell.direction;
	cell = circularBufferGetValue(worm->tailValues, tail->begin);
	screen->chars[cell.position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, cell.direction, nextDirection, worm->headStep)];
}
