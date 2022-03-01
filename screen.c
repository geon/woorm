#include "screen.h"

void screenClear(Screen *screen)
{
	uint16_t i = 0;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = 0;
	}
}
