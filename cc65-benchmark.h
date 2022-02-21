#include <stdbool.h>
#include <stdint.h>

void beginBenchmark(char *messageString);
void endBenchmark();

#define beginBenchmarkRepeat                   \
	{                                          \
		uint8_t _benchmarkRepeatCount = 0x100; \
		do                                     \
		{

#define endBenchmarkRepeat          \
	}                               \
	while (--_benchmarkRepeatCount) \
		;                           \
	}

// #ifndef CLOCKS_PER_SEC
// #define CLOCKS_PER_SEC 1
// #endif
