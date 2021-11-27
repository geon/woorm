#include "screen.h"
#include "tile.h"

void screenClear(Screen *screen)
{
	uint16_t i;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = 0;
	}
}

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 25

void screenDrawLevelBorderRectangle(Screen *screen, uint8_t borderColor)
{
	{
		uint8_t *topChar = screen->chars;
		uint8_t *topColor = screen->colors;
		uint8_t *bottomChar = &screen->chars[SCREEN_WIDTH * (SCREEN_HEIGHT - 1)];
		uint8_t *bottomColor = &screen->colors[SCREEN_WIDTH * (SCREEN_HEIGHT - 1)];
		uint8_t i;

		for (i = 0; i < SCREEN_WIDTH; ++i)
		{
			*topChar = Tile_filled;
			*topColor = borderColor;
			++topChar;
			++topColor;
			*bottomChar = Tile_filled;
			*bottomColor = borderColor;
			++bottomChar;
			++bottomColor;
		}
		--topChar;
		*topChar = Tile_filled;
		screen->chars[0] = Tile_filled;
		--bottomChar;
		*bottomChar = Tile_filled;
		screen->chars[SCREEN_WIDTH * (SCREEN_HEIGHT - 1)] = Tile_filled;
	}

	{
		uint8_t *leftChar = &screen->chars[SCREEN_WIDTH];
		uint8_t *leftColor = &screen->colors[SCREEN_WIDTH];
		uint8_t *rightChar = &screen->chars[SCREEN_WIDTH * 2 - 1];
		uint8_t *rightColor = &screen->colors[SCREEN_WIDTH * 2 - 1];
		uint8_t i;

		for (i = 0; i < SCREEN_HEIGHT - 2; ++i)
		{
			*leftChar = Tile_filled;
			*leftColor = borderColor;
			leftChar += SCREEN_WIDTH;
			leftColor += SCREEN_WIDTH;
			*rightChar = Tile_filled;
			*rightColor = borderColor;
			rightChar += SCREEN_WIDTH;
			rightColor += SCREEN_WIDTH;
		}
	}
}
