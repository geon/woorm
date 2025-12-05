#include "worm.h"
#include "cc65-benchmark.h"
#include "coord.h"
#include "screen.h"
#include "tile.h"
#include "worms.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1
#endif

uint8_t wormIndex = 0;

// Fake screen with char and color ram.
uint8_t chars[1000];
uint8_t colors[1000];
Screen _screen = {
	chars,
	colors};
Screen *screen = &_screen;

void wormBenchmark(void)
{
	screenClear(screen);
	wormInit(wormIndex, screen, coordToPos(coordCreate(4, 0)), Direction_right, 0);

	beginBenchmark("wormStep");
	{
		beginBenchmarkRepeat
			wormStep(wormIndex);
		endBenchmarkRepeat
	}
	endBenchmark();

	beginBenchmark("wormDraw");
	{
		beginBenchmarkRepeat
			wormDraw(wormIndex);
		endBenchmarkRepeat
	}
	endBenchmark();

	beginBenchmark("wormLazyDraw");
	{
		beginBenchmarkRepeat
			wormLazyDraw(wormIndex);
		endBenchmarkRepeat
	}
	endBenchmark();
}
