#include "charset-char.h"
#include <stdbool.h>
#include <stdint.h>

bool charsetCharEquals(CharsetChar a, CharsetChar b)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

void charsetCharCopy(CharsetChar source, CharsetChar destination)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		destination[i] = source[i];
	}
}
