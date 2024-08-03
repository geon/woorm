#include "screen-location-c64.h"

Screen _screen = {
	(uint8_t *)0x0400,
	(uint8_t *)0xD800};
Screen *screen = &_screen;
