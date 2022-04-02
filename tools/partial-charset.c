#include "partial-charset.h"

int partialCharsetFindIndexOrAdd(PartialCharset *charset, CharsetChar charsetChar)
{
	// Avoid adding duplicates.
	int index = charsetIndexOf(charset->charset, charsetChar);
	if (index != -1 && index < charset->numUsedChars)
	{
		return index;
	}

	// New unique char, so add it if not full.
	if (charset->numUsedChars >= 256)
	{
		// Charset is full
		return -1;
	}
	charsetCharCopy(charsetChar, charset->charset[charset->numUsedChars]);
	return charset->numUsedChars++;
}

bool partialCharsetCompress(PartialCharset *compressedCharset, Charset uncompressedCharset, uint8_t mappingTable[256])
{
	for (int index = 0; index < 256; ++index)
	{
		int resultingIndex = partialCharsetFindIndexOrAdd(compressedCharset, uncompressedCharset[index]);
		if (resultingIndex == -1)
		{
			return false;
		}

		mappingTable[index] = (uint8_t)resultingIndex;
	}

	return true;
}
