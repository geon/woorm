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
