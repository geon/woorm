#include "level.h"

void levelRemoveInvisibleColorChanges(Level *level)
{
	for (int i = 0; i < 1000; ++i)
	{
		// If the char is invisible...
		if (!level->chars[i])
		{
			if (i)
			{
				level->colors[i] = level->colors[i - 1];
			}
		}
	}
}

void levelRemapChars(Level *level, Charset newCharset)
{
	for (int i = 0; i < 1000; ++i)
	{
		level->chars[i] = charsetIndexOf(newCharset, (*level->charset)[level->chars[i]]);
	}
}
