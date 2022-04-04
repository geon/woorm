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

void charsetCharPrint(CharsetChar charsetChar)
{
	printf(
		"0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X,\n",
		charsetChar[0],
		charsetChar[1],
		charsetChar[2],
		charsetChar[3],
		charsetChar[4],
		charsetChar[5],
		charsetChar[6],
		charsetChar[7]);
}
