#include "tile.h"
#include "cc65-benchmark.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1
#endif

void tileBenchmark()
{
	beginBenchmark("tileToIndex + tilePackWormTileStateInBits");
	{
		beginBenchmarkRepeat
			tileToIndex[tilePackWormTileStateInBits(1, 1, 1, 1)];
		tileToIndex[tilePackWormTileStateInBits(1, 1, 1, 1)];
		tileToIndex[tilePackWormTileStateInBits(1, 1, 1, 1)];
		tileToIndex[tilePackWormTileStateInBits(1, 1, 1, 1)];
		endBenchmarkRepeat
	}
	endBenchmark();
}
