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
	worm->speed = 4;
	worm->step = Microstep_0;
	worm->color = color;
	worm->screen = screen;
	circularBufferInit(&worm->tail);

	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailDirections, index) = direction;
	circularBufferGetValue(worm->tailPositions, index) = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailDirections, index) = direction;
	circularBufferGetValue(worm->tailPositions, index) = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailDirections, index) = direction;
	circularBufferGetValue(worm->tailPositions, index) = position;
	position += getPositionOffsetForDirection(direction);
	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailDirections, index) = direction;
	circularBufferGetValue(worm->tailPositions, index) = position;

	wormDraw(worm);
}

void wormSetNextDirection(Worm *worm, Direction direction)
{
	worm->wantedNextDirection = direction;
}

void wormSetSpeed(Worm *worm, uint8_t speed)
{
	worm->speed = speed;
}

bool wormGetNextStep(Worm *worm, Direction *nextStepDirection, uint16_t *nextStepPosition)
{
	Direction currentHeadDirection = circularBufferGetLastValue(worm->tail, worm->tailDirections);
	uint16_t currentHeadPosition = circularBufferGetLastValue(worm->tail, worm->tailPositions);

	// Try stepping in the selected direction.
	*nextStepDirection = worm->wantedNextDirection;
	*nextStepPosition = currentHeadPosition + getPositionOffsetForDirection(*nextStepDirection);

	// If the selected direction is blocked, first try the previous direction.
	if (worm->screen->chars[*nextStepPosition])
	{
		*nextStepDirection = circularBufferGetLastValue(worm->tail, worm->tailDirections);
		*nextStepPosition = currentHeadPosition + getPositionOffsetForDirection(*nextStepDirection);
	}
	// If the direction is blocked, turn clockwise.
	if (worm->screen->chars[*nextStepPosition])
	{
		*nextStepDirection = (*nextStepDirection + 1) & 3;
		*nextStepPosition = currentHeadPosition + getPositionOffsetForDirection(*nextStepDirection);
	}
	// If still blocked, try anti-clockwise instead.
	if (worm->screen->chars[*nextStepPosition])
	{
		*nextStepDirection = (*nextStepDirection + 2) & 3;
		*nextStepPosition = currentHeadPosition + getPositionOffsetForDirection(*nextStepDirection);
	}
	// If still blocked, just don't move.
	if (worm->screen->chars[*nextStepPosition])
	{
		return false;
	}

	return true;
}

void wormFullStep(Worm *worm, Direction nextStepDirection, uint16_t nextStepPosition)
{
	uint8_t index = 0;

	circularBufferPush(&worm->tail, &index);
	circularBufferGetValue(worm->tailDirections, index) = nextStepDirection;
	circularBufferGetValue(worm->tailPositions, index) = nextStepPosition;
	circularBufferPop(&worm->tail, &index);
}

void wormStep(Worm *worm)
{
	Direction nextStepDirection = 0;
	uint16_t nextStepPosition = 0;

	bool hasNextStep = false;

	uint8_t stepCounter;
	uint8_t newStep;

	if (worm->speed == 0)
	{
		return;
	}

	for (stepCounter = 0; stepCounter < worm->speed; ++stepCounter)
	{
		hasNextStep = wormGetNextStep(worm, &nextStepDirection, &nextStepPosition);

		newStep = (worm->step + 1) & 15;

		if (newStep == 4)
		{
			if (!hasNextStep)
			{
				// Blocked.
				return;
			}

			wormFullStep(worm, nextStepDirection, nextStepPosition);
		}

		worm->nextDirection = nextStepDirection;

		// When forced to turn, forget whatever input the user did, and continue straight forward.
		worm->wantedNextDirection = worm->nextDirection;

		worm->step = newStep;
	}

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
	Direction direction;
	uint16_t position;
	uint8_t iterator;
	Screen *screen = worm->screen;
	Direction nextDirection = worm->nextDirection;

	circularBufferForEachReverse(tail, iterator)
	{

		direction = circularBufferGetValue(worm->tailDirections, iterator);
		position = circularBufferGetValue(worm->tailPositions, iterator);
		part = wormGetPart(worm, iterator);

		screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(part, direction, nextDirection, worm->step)];
		screen->colors[position] = worm->color;

		nextDirection = direction;
	}
}

void wormLazyDraw(Worm *worm)
{
	Direction nextDirection;
	CircularBuffer *tail = &worm->tail;

	Screen *screen = worm->screen;
	Direction direction;
	uint16_t position;

	// Only the cell just entered needs to have the color changed.
	screen->colors[position] = worm->color;

	nextDirection = worm->nextDirection;
	direction = circularBufferGetValue(worm->tailDirections, tail->end - 1);
	position = circularBufferGetValue(worm->tailPositions, tail->end - 1);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, direction, nextDirection, worm->step)];

	nextDirection = direction;
	direction = circularBufferGetValue(worm->tailDirections, tail->end - 2);
	position = circularBufferGetValue(worm->tailPositions, tail->end - 2);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, direction, nextDirection, worm->step)];

	nextDirection = circularBufferGetValue(worm->tailDirections, worm->tail.begin + 2);
	direction = circularBufferGetValue(worm->tailDirections, tail->begin + 1);
	position = circularBufferGetValue(worm->tailPositions, tail->begin + 1);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, direction, nextDirection, worm->step)];

	nextDirection = direction;
	direction = circularBufferGetValue(worm->tailDirections, tail->begin);
	position = circularBufferGetValue(worm->tailPositions, tail->begin);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, direction, nextDirection, worm->step)];
}
