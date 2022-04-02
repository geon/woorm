#include "partial-charset.h"

int partialCharsetFindIndexOrAdd(PartialCharset *charset, CharsetChar charsetChar)
{
	// Avoid adding duplicates.
	int index = charsetIndexOf(charset->charset, charsetChar);
	if (index != -1 && index < charset->numUsedChars)
	{
		return index;
	}

	// New unique char, so add it.
	charsetCharCopy(charsetChar, charset->charset[charset->numUsedChars]);
	return charset->numUsedChars++;
}
