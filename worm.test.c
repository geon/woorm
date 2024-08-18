#include "worm.h"
#include "cc65-test.h"
#include "coord.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

bool Tile_filled = true;

Worm _worm;
Worm *worm = &_worm;

// Fake screen with char and color ram.
uint8_t chars[1000];
uint8_t colors[1000];
Screen _screen = {
	chars,
	colors};
Screen *screen = &_screen;

void wormTest(void)
{
	beginTest("Create worm.");
	{
		wormInit(worm, screen, 100, Direction_first, 0);
	}
	endTest();

	beginTest("A worm is drawn in 4 tiles on init.");
	{
		screenClear(screen);
		screen->chars[coordToPos(coordCreate(17, 10))] = 1;
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(17, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_0)]);
	}
	endTest();

	beginTest("To move, it must add a tile in front.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_1)]);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_1)]);
	}
	endTest();

	beginTest("Further microsteps should cycle the tiles.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_3)]);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_3)]);
	}
	endTest();

	beginTest("The last microsteps should clear the trail.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);

		assertByte("Head", screen->chars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByte("Middle", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByte("End", screen->chars[coordToPos(coordCreate(19, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_0)]);
		assertByte("Clear", screen->chars[coordToPos(coordCreate(18, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_right, Direction_right, Microstep_0)]);
	}
	endTest();

	beginTest("Setting nextDirection affects macro steps.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_up, 0);
		wormSetNextDirection(worm, Direction_right);

		wormStep(worm);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);

		assertTrue("Head", screen->chars[coordToPos(coordCreate(21, 10))]);
		assertTrue("Middle", screen->chars[coordToPos(coordCreate(20, 10))]);
		assertTrue("End", screen->chars[coordToPos(coordCreate(20, 11))]);
		assertTrue("Clear", !screen->chars[coordToPos(coordCreate(20, 12))]);
	}
	endTest();

	beginTest("Bends should render properly.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_up, 0);
		wormSetNextDirection(worm, Direction_right);

		wormStep(worm);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_0)]);
		assertByteDecimal("Middle", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_up, Direction_right, Microstep_0)]);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(20, 11))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_0)]);
		assertByteDecimal("Clear", screen->chars[coordToPos(coordCreate(20, 12))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_up, Direction_up, Microstep_0)]);
	}
	endTest();

	beginTest("Worms should avoid obstacles automatically.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		screen->chars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(worm);
		assertTrue("Above and to the right.", screen->chars[coordToPos(coordCreate(20, 11))]);

		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		screen->chars[coordToPos(coordCreate(20, 11))] = Tile_filled;
		screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(worm);
		assertTrue("Below and to the right.", screen->chars[coordToPos(coordCreate(20, 9))]);
	}
	endTest();

	beginTest("Worms should not turn back on themself.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_up, 0);
		wormSetNextDirection(worm, Direction_right);
		screen->chars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(worm);
		assertTrue("Above and to the right.", screen->chars[coordToPos(coordCreate(19, 10))]);
	}
	endTest();

	beginTest("Worms should stop if all 4 directions are blocked.");
	{
		uint8_t headTile = 0;
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		screen->chars[coordToPos(coordCreate(20, 9))] = Tile_filled;
		screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		screen->chars[coordToPos(coordCreate(20, 11))] = Tile_filled;

		headTile = screen->chars[coordToPos(coordCreate(20, 10))];
		wormStep(worm);
		assertTrue("No step.", screen->chars[coordToPos(coordCreate(20, 10))] == headTile);
	}
	endTest();

	beginTest("Worms should face forwd when blocked.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		screen->chars[coordToPos(coordCreate(20, 11))] = Tile_filled;
		wormSetNextDirection(worm, Direction_down);

		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_head, Direction_right, Direction_right, Microstep_1)]);
	}
	endTest();

	beginTest("Worms look ahead around corners.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_up, 0);
		// screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;
		wormStep(worm);
		wormSetNextDirection(worm, Direction_right);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(20, 9))], tilePackWormTileStateInBits(TileType_animated_head, Direction_up, Direction_right, Microstep_2));
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_2)]);
		assertByteDecimal("Head to end", screen->chars[coordToPos(coordCreate(20, 11))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_2)]);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(20, 12))], tileToIndex[tilePackWormTileStateInBits(TileType_animated_end, Direction_up, Direction_up, Microstep_2)]);
	}
	endTest();

	beginTest("Worms forget wanted direction.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormSetNextDirection(worm, Direction_right);
		screen->chars[coordToPos(coordCreate(21, 10))] = Tile_filled;

		wormStep(worm);

		assertByteDecimal("Direction", worm->wantedNextDirection, (Direction_right + 1) % 4);
	}
	endTest();
}
