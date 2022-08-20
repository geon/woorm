#include "level.test.h"
#include "../cc65-test.h"
#include "level.h"

void levelTest(void)
{
	beginTest("Remove invisible color changes.");
	{
		Level level;

		// Visible color changes.
		level.chars[0] = 1;
		level.chars[1] = 2;
		level.chars[2] = 3;
		level.colors[0] = 1;
		level.colors[1] = 2;
		level.colors[2] = 3;

		// Invisible color changes.
		level.chars[3] = 0;
		level.chars[4] = 0;
		level.chars[5] = 0;
		level.colors[3] = 1;
		level.colors[4] = 2;
		level.colors[5] = 3;

		// TODO: Actually look at the charset to figure out if there are any pixels with the primary color.
		levelRemoveInvisibleColorChanges(&level);

		assertByteDecimal("Visible 1", level.colors[0], 1);
		assertByteDecimal("Visible 2", level.colors[1], 2);
		assertByteDecimal("Visible 3", level.colors[2], 3);

		assertByteDecimal("Invisible 1", level.colors[3], 3);
		assertByteDecimal("Invisible 2", level.colors[4], 3);
		assertByteDecimal("Invisible 3", level.colors[5], 3);
	}
	endTest();
}
