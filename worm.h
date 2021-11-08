#ifndef WORM_H
#define WORM_H

#include "direction.h"
#include "screen.h"
#include <stdint.h>

typedef struct Worm
{
	char placeholder;
} Worm;

void wormInit(Worm *worm, Screen *screen, uint16_t pos, Direction direction);

#endif
