#include "worm.h"
#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "tile.h"
#include "worms.h"
#include <stdint.h>

void wormInitAddSegment(uint8_t wormIndex, uint16_t *position, Direction direction, uint8_t *segmentIndex)
{
	circularBufferPush(worms.tailBegin[wormIndex], &worms.tailEnd[wormIndex], segmentIndex);
	circularBufferGetValue(worms.tailDirections[wormIndex], *segmentIndex) = direction;
	circularBufferGetValue(worms.tailPositions[wormIndex], *segmentIndex) = *position;
	*position += getPositionOffsetForDirection(direction);
}

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction)
{
	uint8_t index = 0;
	uint16_t position = pos - getPositionOffsetForDirection(direction) * 3;

	worms.wantedNextDirection[wormIndex] = direction;
	worms.nextDirection[wormIndex] = direction;
	worms.headStep[wormIndex] = Microstep_0;
	worms.tailStep[wormIndex] = Microstep_0;
	circularBufferInit(&worms.tailBegin[wormIndex], &worms.tailEnd[wormIndex]);
	worms.hasNextStep[wormIndex] = false;

	wormInitAddSegment(wormIndex, &position, direction, &index);
	wormInitAddSegment(wormIndex, &position, direction, &index);
	wormInitAddSegment(wormIndex, &position, direction, &index);
	wormInitAddSegment(wormIndex, &position, direction, &index);

	wormDraw(wormIndex);
}

void wormSetNextDirection(uint8_t wormIndex, Direction direction)
{
	worms.wantedNextDirection[wormIndex] = direction;
}

void wormSetNextStep(uint8_t wormIndex)
{

	uint16_t currentHeadPosition = circularBufferGetLastValue(worms.tailEnd[wormIndex], worms.tailPositions[wormIndex]);

	// Try stepping in the selected direction.
	worms.nextStepDirection[wormIndex] = worms.wantedNextDirection[wormIndex];
	worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);
	worms.hasNextStep[wormIndex] = true;

	// If the selected direction is blocked, first try the previous direction.
	if (screen->chars[worms.nextStepPosition[wormIndex]])
	{
		worms.nextStepDirection[wormIndex] = circularBufferGetLastValue(worms.tailEnd[wormIndex], worms.tailDirections[wormIndex]);
		worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);
	}
	// If the direction is blocked, turn clockwise.
	if (screen->chars[worms.nextStepPosition[wormIndex]])
	{
		worms.nextStepDirection[wormIndex] = (worms.nextStepDirection[wormIndex] + 1) & 0b11;
		worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);
	}
	// If still blocked, try anti-clockwise instead.
	if (screen->chars[worms.nextStepPosition[wormIndex]])
	{
		worms.nextStepDirection[wormIndex] = (worms.nextStepDirection[wormIndex] + 2) & 0b11;
		worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);
	}
	// If still blocked, just don't move.
	if (screen->chars[worms.nextStepPosition[wormIndex]])
	{
		worms.hasNextStep[wormIndex] = false;
	}
}

void wormStep(uint8_t wormIndex)
{

	// TODO: Run this only each full step. Worms don't need to be able to change direction in the middle of a step.
	wormSetNextStep(wormIndex);

	if (worms.headStep[wormIndex] == 0 && worms.hasNextStep[wormIndex])
	{
		uint8_t index = 0;
		circularBufferPush(worms.tailBegin[wormIndex], &worms.tailEnd[wormIndex], &index);
		circularBufferGetValue(worms.tailDirections[wormIndex], index) = worms.nextStepDirection[wormIndex];
		circularBufferGetValue(worms.tailPositions[wormIndex], index) = worms.nextStepPosition[wormIndex];
	}

	if (!worms.hasNextStep[wormIndex])
	{
		// Blocked.
		return;
	}

	if (worms.tailStep[wormIndex] == 0)
	{
		uint8_t index = 0;

		circularBufferPop(&worms.tailBegin[wormIndex], worms.tailEnd[wormIndex], &index);
	}

	worms.headStep[wormIndex] = (worms.headStep[wormIndex] + 4) & 0b1111;
	worms.tailStep[wormIndex] = (worms.tailStep[wormIndex] + 4) & 0b1111;

	worms.nextDirection[wormIndex] = worms.nextStepDirection[wormIndex];

	// When forced to turn, forget whatever input the user did, and continue straight forward.
	worms.wantedNextDirection[wormIndex] = worms.nextDirection[wormIndex];

	wormLazyDraw(wormIndex);
}

TileType wormGetPart(uint8_t wormIndex, uint8_t iterator);

TileType wormGetPart(uint8_t wormIndex, uint8_t iterator)
{

	TileType part = 0;
	if (iterator == worms.tailEnd[wormIndex] - 1)
	{
		part = TileType_animated_head;
	}
	else if (iterator == worms.tailEnd[wormIndex] - 2)
	{
		part = TileType_animated_headToMiddle;
	}
	else if (iterator == worms.tailBegin[wormIndex] + 1)
	{
		part = TileType_animated_endToMiddle;
	}
	else if (iterator == worms.tailBegin[wormIndex])
	{
		part = TileType_animated_end;
	}
	else
	{
		part = TileType_middle;
	}

	return part;
}

void wormDraw(uint8_t wormIndex)
{
	uint8_t color = wormColors[wormIndex] + 8;

	TileType part = 0;
	Direction direction;
	uint16_t position;
	uint8_t iterator;
	Direction nextDirection = worms.nextDirection[wormIndex];

	circularBufferForEachReverse(worms.tailBegin[wormIndex], worms.tailEnd[wormIndex], iterator)
	{

		direction = circularBufferGetValue(worms.tailDirections[wormIndex], iterator);
		position = circularBufferGetValue(worms.tailPositions[wormIndex], iterator);
		part = wormGetPart(wormIndex, iterator);

		// TODO. This call uses only the head step, not the tail step.
		screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(part, direction, nextDirection, worms.headStep[wormIndex])];
		screen->colors[position] = color;

		nextDirection = direction;
	}
}

uint8_t wormLazyDraw_color;
Direction wormLazyDraw_direction;
Direction *wormLazyDraw_tailDirections;
uint16_t *wormLazyDraw_tailPositions;
void wormLazyDrawTile(
	Direction nextDirection,
	uint8_t tailIndex,
	TileType tileType,
	Microstep step)
{
	uint16_t position = circularBufferGetValue(wormLazyDraw_tailPositions, tailIndex);
	wormLazyDraw_direction = circularBufferGetValue(wormLazyDraw_tailDirections, tailIndex);
	screen->chars[position] = tileToIndex[tilePackWormTileStateInBits(tileType, wormLazyDraw_direction, nextDirection, step)];
	// TODO: Only needed on full steps.
	// TODO:
	// Only the cell just entered needs to have the color changed.
	screen->colors[position] = wormLazyDraw_color;
}
void wormLazyDraw(uint8_t wormIndex)
{
	uint16_t tailBegin = worms.tailBegin[wormIndex];
	uint16_t tailEnd = worms.tailEnd[wormIndex];

	wormLazyDraw_color = wormColors[wormIndex] + 8;
	wormLazyDraw_tailDirections = worms.tailDirections[wormIndex];
	wormLazyDraw_tailPositions = worms.tailPositions[wormIndex];

	{
		Direction nextDirection = worms.nextDirection[wormIndex];
		uint8_t tailIndex = tailEnd - 1;
		TileType tileType = TileType_animated_head;
		Microstep step = worms.headStep[wormIndex];
		wormLazyDrawTile(nextDirection, tailIndex, tileType, step);
	}

	{
		Direction nextDirection = wormLazyDraw_direction;
		uint8_t tailIndex = tailEnd - 2;
		TileType tileType = TileType_animated_headToMiddle;
		Microstep step = worms.headStep[wormIndex];
		wormLazyDrawTile(nextDirection, tailIndex, tileType, step);
	}

	{
		Direction nextDirection = circularBufferGetValue(wormLazyDraw_tailDirections, tailBegin + 2);
		uint8_t tailIndex = tailBegin + 1;
		TileType tileType = TileType_animated_endToMiddle;
		Microstep step = worms.tailStep[wormIndex];
		wormLazyDrawTile(nextDirection, tailIndex, tileType, step);
	}

	{
		Direction nextDirection = wormLazyDraw_direction;
		uint8_t tailIndex = tailBegin;
		TileType tileType = TileType_animated_end;
		Microstep step = worms.tailStep[wormIndex];
		wormLazyDrawTile(nextDirection, tailIndex, tileType, step);
	}
}
