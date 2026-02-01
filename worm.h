#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include "microstep.h"
#include "screen.h"
#include "tile-type.h"
#include <stdint.h>

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction);
void wormSetNextDirection(uint8_t wormIndex, Direction direction);
void wormStep(uint8_t wormIndex);

// For benchmark only.
void wormDraw(uint8_t wormIndex);
void wormLazyDraw(uint8_t wormIndex);

#endif
