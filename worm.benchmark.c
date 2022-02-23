#include "worm.h"
#include "cc65-benchmark.h"
#include "coord.h"
#include "screen.h"
#include "tile.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1
#endif

Worm _worm;
Worm *worm = &_worm;

// Fake screen with char and color ram.
uint8_t chars[1000];
uint8_t colors[1000];
Screen _screen = {
	chars,
	colors};
Screen *screen = &_screen;

void wormBenchmark()
{
	screenClear(screen);
	wormInit(worm, screen, coordToPos(coordCreate(4, 0)), Direction_right, 0);

	beginBenchmark("wormStep");
	{
		beginBenchmarkRepeat
			wormStep(worm);
		endBenchmarkRepeat
	}
	endBenchmark();

	beginBenchmark("wormDrawCell");
	{
		beginBenchmarkRepeat
			Direction nextDirection = Direction_right;
		wormDrawCell(worm, worm->tail.end - 1, &nextDirection, 0);
		endBenchmarkRepeat
	}
	endBenchmark();

	beginBenchmark("wormDraw");
	{
		beginBenchmarkRepeat
			wormDraw(worm);
		endBenchmarkRepeat
	}
	endBenchmark();

	beginBenchmark("wormLazyDraw");
	{
		beginBenchmarkRepeat
			wormLazyDraw(worm);
		endBenchmarkRepeat
	}
	endBenchmark();
}
