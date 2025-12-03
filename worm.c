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
	worm->tailStep = Microstep_0;
	worm->color = color;
	worm->screen = screen;
	circularBufferInit(&worm->tail);
	worm->hasNextStep = false;

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

void wormSetNextStep(Worm *worm)
{
	uint16_t currentHeadPosition = circularBufferGetLastValue(worm->tail, worm->tailPositions);

	// Try stepping in the selected direction.
	worm->nextStep.direction = worm->wantedNextDirection;
	worm->nextStep.position = currentHeadPosition + getPositionOffsetForDirection(worm->nextStep.direction);
	worm->hasNextStep = true;

	// If the selected direction is blocked, first try the previous direction.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = circularBufferGetLastValue(worm->tail, worm->tailDirections);
		worm->nextStep.position = currentHeadPosition + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If the direction is blocked, turn clockwise.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = (worm->nextStep.direction + 1) & 0b11;
		worm->nextStep.position = currentHeadPosition + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If still blocked, try anti-clockwise instead.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->nextStep.direction = (worm->nextStep.direction + 2) & 0b11;
		worm->nextStep.position = currentHeadPosition + getPositionOffsetForDirection(worm->nextStep.direction);
	}
	// If still blocked, just don't move.
	if (worm->screen->chars[worm->nextStep.position])
	{
		worm->hasNextStep = false;
	}
}

void wormStep(Worm *worm)
{
	// TODO: Run this only each full step. Worms don't need to be able to change direction in the middle of a step.
	wormSetNextStep(worm);

	worm->headStep = (worm->headStep + 4) & 0b1111;
	worm->tailStep = (worm->tailStep + 4) & 0b1111;

	if (worm->headStep == 4)
	{
		uint8_t index = 0;

		if (!worm->hasNextStep)
		{
			// Blocked.
			return;
		}

		circularBufferPush(&worm->tail, &index);
		circularBufferGetValue(worm->tailDirections, index) = worm->nextStep.direction;
		circularBufferGetValue(worm->tailPositions, index) = worm->nextStep.position;
	}

	if (worm->tailStep == 4)
	{
		uint8_t index = 0;

		circularBufferPop(&worm->tail, &index);
	}

	worm->nextDirection = worm->nextStep.direction;

	// When forced to turn, forget whatever input the user did, and continue straight forward.
	worm->wantedNextDirection = worm->nextDirection;

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

		// TODO. This call uses only the head step, not the tail step.
		screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(part, direction, nextDirection, worm->headStep)];
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

	nextDirection = worm->nextDirection;
	direction = circularBufferGetValue(worm->tailDirections, tail->end - 1);
	position = circularBufferGetValue(worm->tailPositions, tail->end - 1);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, direction, nextDirection, worm->headStep)];

	// TODO: Only needed on full steps.
	// Only the cell just entered needs to have the color changed.
	screen->colors[position] = worm->color;

	nextDirection = direction;
	direction = circularBufferGetValue(worm->tailDirections, tail->end - 2);
	position = circularBufferGetValue(worm->tailPositions, tail->end - 2);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, direction, nextDirection, worm->headStep)];

	nextDirection = circularBufferGetValue(worm->tailDirections, worm->tail.begin + 2);
	direction = circularBufferGetValue(worm->tailDirections, tail->begin + 1);
	position = circularBufferGetValue(worm->tailPositions, tail->begin + 1);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, direction, nextDirection, worm->tailStep)];

	nextDirection = direction;
	direction = circularBufferGetValue(worm->tailDirections, tail->begin);
	position = circularBufferGetValue(worm->tailPositions, tail->begin);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, direction, nextDirection, worm->tailStep)];
}
