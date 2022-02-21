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
	beginBenchmark("tileCreate");
	{
		beginBenchmarkRepeat
			tileCreate(1, 1, 1, 1);
		tileCreate(1, 1, 1, 1);
		tileCreate(1, 1, 1, 1);
		tileCreate(1, 1, 1, 1);
		endBenchmarkRepeat
	}
	endBenchmark();
}
