#include "screen.h"
#include <c64.h>
#include <conio.h>
#include <stdint.h>

Screen _screen = {
	(uint8_t *)0x0400,
	(uint8_t *)0xD800};
Screen *screen = &_screen;

void clearScreen()
{
	uint16_t i;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = 0;
	}
}

int main()
{
	clearScreen();
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);

	return 0;
}
