#include "charset.h"
#include <stdio.h>

int charsetIndexOf(Charset charset, CharsetChar charsetChar)
{
	for (int i = 0; i < 256; ++i)
	{
		if (charsetCharEquals(charset[i], charsetChar))
		{
			return i;
		}
	}

	return -1;
}

void charsetPrint(Charset charset)
{
	printf("\n{\n");
	for (int i = 0; i < 256; ++i)
	{
		charsetCharPrint(charset[i]);
	}
	printf("}\n");
}
