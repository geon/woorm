#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "worm.h"
#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

Worm wormPlayer1;
Worm wormPlayer2;
Worm wormPlayer3;
Worm wormPlayer4;

Screen _screen = {
	(uint8_t *)0x0400,
	(uint8_t *)0xD800};
Screen *screen = &_screen;

void animateWorm(Worm *worm)
{
	wormStep(worm);
	if (worm->step == 0)
	{
		int random = rand() % 4;
		worm->nextDirection = (worm->nextDirection + (random == 0 ? 1 : (random == 1 ? -1 : 0))) & 3;
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

void waitMs(uint16_t time)
{
	uint16_t frames = time / 20;
	uint8_t i;
	for (i = 0; i < frames; ++i)
	{
		waitvsync();
	}
}

int main()
{
	srand(time(NULL));

	screenClear(screen);
	bgcolor(COLOR_BLACK);
	bordercolor(COLOR_BLACK);
	setUpWormCharset();

	waitMs(1000);

	wormInit(&wormPlayer1, screen, coordToPos(coordCreate(10, 10)), Direction_right, COLOR_GREEN + 8);
	wormInit(&wormPlayer2, screen, coordToPos(coordCreate(20, 20)), Direction_up, COLOR_YELLOW + 8);
	wormInit(&wormPlayer3, screen, coordToPos(coordCreate(10, 14)), Direction_down, COLOR_RED + 8);
	wormInit(&wormPlayer4, screen, coordToPos(coordCreate(30, 14)), Direction_left, COLOR_CYAN + 8);

	for (;;)
	{
		waitMs(40);
		animateWorm(&wormPlayer1);
		animateWorm(&wormPlayer2);
		animateWorm(&wormPlayer3);
		animateWorm(&wormPlayer4);
	}

	return 0;
}
