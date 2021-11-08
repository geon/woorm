#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

typedef struct Screen
{
	uint8_t *chars;
	uint8_t *colors;
} Screen;

#endif
