#include "charset.h"

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
