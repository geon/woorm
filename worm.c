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
	worms.tailDirections[wormIndex][*segmentIndex] = direction;
	worms.tailPositions[wormIndex][*segmentIndex] = *position;
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
	uint8_t lastTailIndex = worms.tailEnd[wormIndex] - 1;
	uint16_t currentHeadPosition = worms.tailPositions[wormIndex][lastTailIndex];

	// Try stepping in the selected direction.
	worms.nextStepDirection[wormIndex] = worms.wantedNextDirection[wormIndex];
	worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);
	worms.hasNextStep[wormIndex] = true;

	// Check if not blocked.
	if (!screenChars[worms.nextStepPosition[wormIndex]])
	{
		return;
	}

	// The selected direction is blocked, first try the previous direction.
	worms.nextStepDirection[wormIndex] = worms.tailDirections[wormIndex][lastTailIndex];
	worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);

	// Check if not blocked.
	if (!screenChars[worms.nextStepPosition[wormIndex]])
	{
		return;
	}

	// The direction is blocked, turn clockwise.
	worms.nextStepDirection[wormIndex] = (worms.nextStepDirection[wormIndex] + 1) & 0b11;
	worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);

	// Check if not blocked.
	if (!screenChars[worms.nextStepPosition[wormIndex]])
	{
		return;
	}

	// Still blocked, try anti-clockwise instead.
	worms.nextStepDirection[wormIndex] = (worms.nextStepDirection[wormIndex] + 2) & 0b11;
	worms.nextStepPosition[wormIndex] = currentHeadPosition + getPositionOffsetForDirection(worms.nextStepDirection[wormIndex]);

	// Check if not blocked.
	if (!screenChars[worms.nextStepPosition[wormIndex]])
	{
		return;
	}

	// Still blocked, just don't move.
	worms.hasNextStep[wormIndex] = false;
}

void wormStep(uint8_t wormIndex)
{

	// TODO: Run this only each full step. Worms don't need to be able to change direction in the middle of a step.
	wormSetNextStep(wormIndex);

	if (!worms.hasNextStep[wormIndex])
	{
		// Blocked.
		return;
	}

	if (worms.headStep[wormIndex] == 0)
	{
		uint8_t index = 0;
		circularBufferPush(worms.tailBegin[wormIndex], &worms.tailEnd[wormIndex], &index);
		worms.tailDirections[wormIndex][index] = worms.nextStepDirection[wormIndex];
		worms.tailPositions[wormIndex][index] = worms.nextStepPosition[wormIndex];
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

		direction = worms.tailDirections[wormIndex][iterator];
		position = worms.tailPositions[wormIndex][iterator];
		part = wormGetPart(wormIndex, iterator);

		// TODO. This call uses only the head step, not the tail step.
		screenChars[position] = tileToIndex[tilePackWormTileStateInBits(part, direction, nextDirection, worms.headStep[wormIndex])];
		screenColors[position] = color;

		nextDirection = direction;
	}
}

uint8_t wormLazyDraw_color;
Direction wormLazyDraw_direction;
Direction *wormLazyDraw_tailDirections;
uint16_t *wormLazyDraw_tailPositions;
Direction wormLazyDraw_nextDirection;
TileType wormLazyDraw_type;
Microstep wormLazyDraw_step;
uint8_t wormLazyDraw_tailIndex;
uint8_t wormLazyDraw_getTile()
{
	// Optimized tilePackWormTileStateInBits
	return (
		// 3 bits, but the top bit isn't used.
		((uint8_t)wormLazyDraw_type << 6) |
		((uint8_t)wormLazyDraw_direction << 4) |
		((uint8_t)wormLazyDraw_step & 0b1100) |
		((uint8_t)wormLazyDraw_nextDirection << 0));
}
void wormLazyDrawTile()
{
	uint16_t position = wormLazyDraw_tailPositions[wormLazyDraw_tailIndex];
	uint8_t tile;

	wormLazyDraw_direction = wormLazyDraw_tailDirections[wormLazyDraw_tailIndex];

	tile = wormLazyDraw_getTile();
	screenChars[position] = tileToIndex[tile];
	// TODO: Only needed on full steps.
	// TODO:
	// Only the cell just entered needs to have the color changed.
	screenColors[position] = wormLazyDraw_color;
}
void wormLazyDraw(uint8_t wormIndex)
{
	uint16_t tailBegin = worms.tailBegin[wormIndex];
	uint16_t tailEnd = worms.tailEnd[wormIndex];
	Microstep headStep = worms.headStep[wormIndex];
	Microstep tailStep = worms.tailStep[wormIndex];

	wormLazyDraw_color = wormColors[wormIndex] + 8;
	wormLazyDraw_tailDirections = worms.tailDirections[wormIndex];
	wormLazyDraw_tailPositions = worms.tailPositions[wormIndex];

	wormLazyDraw_nextDirection = worms.nextDirection[wormIndex];
	wormLazyDraw_type = TileType_animated_head;
	wormLazyDraw_step = headStep;
	wormLazyDraw_tailIndex = tailEnd - 1;
	wormLazyDrawTile();

	wormLazyDraw_nextDirection = wormLazyDraw_direction;
	wormLazyDraw_type = TileType_animated_headToMiddle;
	wormLazyDraw_step = headStep;
	wormLazyDraw_tailIndex = tailEnd - 2;
	wormLazyDrawTile();

	wormLazyDraw_nextDirection = wormLazyDraw_tailDirections[tailBegin + 2];
	wormLazyDraw_type = TileType_animated_endToMiddle;
	wormLazyDraw_step = tailStep;
	wormLazyDraw_tailIndex = tailBegin + 1;
	wormLazyDrawTile();

	wormLazyDraw_nextDirection = wormLazyDraw_direction;
	wormLazyDraw_type = TileType_animated_end;
	wormLazyDraw_step = tailStep;
	wormLazyDraw_tailIndex = tailBegin;
	wormLazyDrawTile();
}
