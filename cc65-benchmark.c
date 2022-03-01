#include "cc65-benchmark.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

char *currentBenchmarkMessageStringPointer = NULL;
time_t begin;

void beginBenchmark(char *messageString)
{
	currentBenchmarkMessageStringPointer = messageString;
	begin = clock();
}

void endBenchmark(void)
{
	printf("%-20s%5i f\n", currentBenchmarkMessageStringPointer, (int)(clock() - begin));
}
