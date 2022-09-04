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

	beginTest("Remap chars to new charset.");
	{
		Charset oldCharset;
		for (int i = 0; i < 256; ++i)
		{
			oldCharset[i][0] = (uint8_t)i;
			oldCharset[i][1] = (uint8_t)i;
			oldCharset[i][2] = (uint8_t)i;
			oldCharset[i][3] = (uint8_t)i;
			oldCharset[i][4] = (uint8_t)i;
			oldCharset[i][5] = (uint8_t)i;
			oldCharset[i][6] = (uint8_t)i;
			oldCharset[i][7] = (uint8_t)i;
		}

		Charset newCharset;
		for (int i = 0; i < 256; ++i)
		{
			newCharset[i][0] = 255 - (uint8_t)i;
			newCharset[i][1] = 255 - (uint8_t)i;
			newCharset[i][2] = 255 - (uint8_t)i;
			newCharset[i][3] = 255 - (uint8_t)i;
			newCharset[i][4] = 255 - (uint8_t)i;
			newCharset[i][5] = 255 - (uint8_t)i;
			newCharset[i][6] = 255 - (uint8_t)i;
			newCharset[i][7] = 255 - (uint8_t)i;
		}

		Level level;
		level.charset = &oldCharset;
		level.chars[0] = 0;
		level.chars[1] = 1;
		level.chars[2] = 2;

		levelRemapChars(&level, &newCharset);

		assertByteDecimal("chars[0]", level.chars[0], 255);
		assertByteDecimal("chars[1]", level.chars[1], 254);
		assertByteDecimal("chars[2]", level.chars[2], 253);
	}
	endTest();
}
