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
		wormInit(worm, screen, 100, Direction_first);
	}
	endTest();

	beginTest("A worm is drawn in 4 tiles on init.");
	{
		screen->chars[coordToPos(coordCreate(17, 10))] = 1;
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_0_0);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_1_0);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(18, 10))], Tile_worm_right_2_0);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(17, 10))], Tile_empty);
	}
	endTest();

	beginTest("To move, it must add a tile in front.");
	{
		wormInit(worm, screen, coordToPos(coordCreate(20, 10)), Direction_right);
		wormStep(worm);

		assertByteDecimal("Head", screen->chars[coordToPos(coordCreate(21, 10))], Tile_worm_right_0_1);
		assertByteDecimal("Head to middle", screen->chars[coordToPos(coordCreate(20, 10))], Tile_worm_right_1_1);
		assertByteDecimal("End to middle", screen->chars[coordToPos(coordCreate(19, 10))], Tile_worm_right_2_1);
		assertByteDecimal("End", screen->chars[coordToPos(coordCreate(18, 10))], Tile_worm_right_3_1);
	}
	endTest();
}
