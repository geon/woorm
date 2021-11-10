#include "screen.h"
#include "worm.h"
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

void setUpWormCharset()
{
	// Switch to charset at 0x2000. (Charset with index 4 in the default bank, which is the first one not shadowed by rom.)
	// 0xD018
	VIC.addr = (VIC.addr & 0xF0) | (4 << 1);

	// Switch to multi color mode.
	// 0xD016
	VIC.ctrl2 = VIC.ctrl2 | 16;

	// Set up secondary char colors.
	// 0xD022
	VIC.bgcolor1 = COLOR_WHITE;
	// 0xD023
	VIC.bgcolor2 = COLOR_BROWN;
}

int main()
{
	clearScreen();
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);
	setUpWormCharset();

	return 0;
}
