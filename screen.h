#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

typedef struct Screen
{
	uint8_t *chars;
	uint8_t *colors;
} Screen;

void screenClear(Screen *screen);
void screenDrawLevelBorderRectangle(Screen *screen, uint8_t borderColor);

#endif
