#include "charset-char.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

bool charsetCharHasPrimaryColor(CharsetChar charsetChar)
{
	// Check all lines.
	for (int i = 0; i < 8; ++i)
	{
		uint8_t line = charsetChar[i];

		// Check all bit-pairs.
		for (int j = 0; j < 4; ++j)
		{
			uint8_t bitPair = (line >> (j * 2)) & 0b11;

			if (bitPair == 0b01)
			{
				return true;
			}
		}
	}

	return false;
}
