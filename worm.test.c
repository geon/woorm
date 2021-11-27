#include "worm.h"
#include "cc65-test.h"
#include "coord.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>

Worm _worm;
Worm *worm = &_worm;

// Fake screen with char and color ram.
uint8_t chars[1000];
uint8_t colors[1000];
Screen _screen = {
	chars,
	colors};
Screen *screen = &_screen;

void wormTest()
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

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_0_0);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_1_0);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(18, 10))], Tile_worm_right_2_0);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(17, 10))], Tile_empty);
	}
	endTest();

	beginTest("To move, it must add a tile in front.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], Tile_worm_right_0_1);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_1_1);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_2_1);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(18, 10))], Tile_worm_right_3_1);
	}
	endTest();

	beginTest("Further microsteps should cycle the tiles.");
	{
		screenClear(screen);
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right, 0);
		wormStep(worm);
		wormStep(worm);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], Tile_worm_right_0_3);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_1_3);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_2_3);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(18, 10))], Tile_worm_right_3_3);
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

		assertByte("Head", screen->chars[coordToPos(coordCreate(21, 10))], Tile_worm_right_0_0);
		assertByte("Middle", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_1_0);
		assertByte("End", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_2_0);
		assertByte("Clear", screen->chars[coordToPos(coordCreate(18, 10))], Tile_empty);
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

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], Tile_worm_right_0_0);
		assertByteDecimal("Middle", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_up_right_1_0);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(20, 11))], Tile_worm_up_2_0);
		assertByteDecimal("Clear", screen->chars[coordToPos(coordCreate(20, 12))], Tile_empty);
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
	}
	endTest();
}
