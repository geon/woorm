#include "tile.benchmark.h"
#include "worm.benchmark.h"
#include <c64.h>
#include <stdio.h>

int main(void)
{
	printf("\ntile.c\n----------\n");
	tileBenchmark();

	printf("\nworm.c\n----------\n");
	wormBenchmark();

	return 0;
}
