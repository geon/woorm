#include "worms.h"
#ifdef __C64__
#include <c64.h>
#else
#define COLOR_CYAN 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_RED 4
#endif

Worm worms[4];

uint8_t wormColors[4] = {
	COLOR_CYAN,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_RED,
};
