#include "screen.h"

void screenClear(Screen *screen)
{
	uint16_t i;

	for (i = 0; i < 1000; ++i)
	{
		screen->chars[i] = 0;
	}
}
