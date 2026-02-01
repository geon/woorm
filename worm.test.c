#include "worm.h"
#include "cc65-test.h"
#include "coord.h"
#include "screen.h"
#include "tile.h"
#include "worms.h"
#include <stdint.h>

bool Tile_filled = true;

uint8_t wormIndex = 0;

// Fake screen with char and color ram.
uint8_t chars[1000];
uint8_t colors[1000];
uint8_t *screenChars = chars;
uint8_t *screenColors = colors;

void wormTest(void)
{
	beginTest("Create worm.");
	{
		wormInit(wormIndex, 100, Direction_first);
	}
	endTest();

	beginTest("A worm is drawn in 4 tiles on init.");
	{
		screenClear();
		screenChars[coordToPos(coordCreate(17, 10))] = 1;
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("Head to middle", screenChars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("End to middle", screenChars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("End", screenChars[coordToPos(coordCreate(17, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_0)]);
	}
	endTest();

	beginTest("To move, it must add a tile in front.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		wormStep(wormIndex);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("Head to middle", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("End to middle", screenChars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("End", screenChars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_1)]);
	}
	endTest();

	beginTest("Further microsteps should cycle the tiles.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("Head to middle", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("End to middle", screenChars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("End", screenChars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_3)]);
	}
	endTest();

	beginTest("The last microsteps should clear the trail.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);

		assertByte("Head", screenChars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByte("Middle", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByte("End", screenChars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByte("Clear", screenChars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_0)]);
	}
	endTest();

	beginTest("Setting nextDirection affects macro steps.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_up);
		wormSetNextDirection(wormIndex, Direction_right);

		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);

		assertTrue("Head", screenChars[coordToPos(coordCreate(21, 10))]);
		assertTrue("Middle", screenChars[coordToPos(coordCreate(20, 10))]);
		assertTrue("End", screenChars[coordToPos(coordCreate(20, 11))]);
		assertTrue("Clear", !screenChars[coordToPos(coordCreate(20, 12))]);
	}
	endTest();

	beginTest("Bends should render properly.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_up);
		wormSetNextDirection(wormIndex, Direction_right);

		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);
		wormStep(wormIndex);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("Middle", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_up, Direction_right, Microstep_0)]);
		assertByteDecimal("End", screenChars[coordToPos(coordCreate(20, 11))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_0)]);
		assertByteDecimal("Clear", screenChars[coordToPos(coordCreate(20, 12))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_up, Direction_up, Microstep_0)]);
	}
	endTest();

	beginTest("Worms should avoid obstacles automatically.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		screenChars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(wormIndex);
		assertTrue("Above and to the right.", screenChars[coordToPos(coordCreate(20, 11))]);

		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		screenChars[coordToPos(coordCreate(20, 11))] = Tile_filled;
		screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(wormIndex);
		assertTrue("Below and to the right.", screenChars[coordToPos(coordCreate(20, 9))]);
	}
	endTest();

	beginTest("Worms should not turn back on themself.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_up);
		wormSetNextDirection(wormIndex, Direction_right);
		screenChars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(wormIndex);
		assertTrue("Above and to the right.", screenChars[coordToPos(coordCreate(19, 10))]);
	}
	endTest();

	beginTest("Worms should stop if all 4 directions are blocked.");
	{
		uint8_t headTile = 0;
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		screenChars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		screenChars[coordToPos(coordCreate(20, 11))] = Tile_filled;

		headTile = screenChars[coordToPos(coordCreate(20, 10))];
		wormStep(wormIndex);
		assertTrue("No headStep.", screenChars[coordToPos(coordCreate(20, 10))] == headTile);
	}
	endTest();

	beginTest("Worms should face forwd when blocked.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		screenChars[coordToPos(coordCreate(20, 11))] = Tile_filled;
		wormSetNextDirection(wormIndex, Direction_down);

		wormStep(wormIndex);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_1)]);
	}
	endTest();

	beginTest("Worms look ahead around corners.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_up);
		// screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(wormIndex);
		wormSetNextDirection(wormIndex, Direction_right);
		wormStep(wormIndex);

		assertByteDecimal("Head", screenChars[coordToPos(coordCreate(20, 9))], tilePackWormTileStateInBits(TileType_animated_head, Direction_up, Direction_right, Microstep_2));
		assertByteDecimal("Head to middle", screenChars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_2)]);
		assertByteDecimal("Head to end", screenChars[coordToPos(coordCreate(20, 11))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_2)]);
		assertByteDecimal("End", screenChars[coordToPos(coordCreate(20, 12))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_up, Direction_up, Microstep_2)]);
	}
	endTest();

	beginTest("Worms forget wanted direction.");
	{
		screenClear();
		wormInit(wormIndex, coordToPos(coordCreate(20, 10)), Direction_right);
		wormSetNextDirection(wormIndex, Direction_right);
		screenChars[coordToPos(coordCreate(21, 10))] = Tile_filled;

		wormStep(wormIndex);

		assertByteDecimal("Direction", worms.wantedNextDirection[wormIndex], (Direction_right + 1) % 4);
	}
	endTest();
}
